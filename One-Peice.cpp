#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<vector>
#include<sstream>
#include<cstring>
#include<fcntl.h>
using namespace std;
int main(){
    string input;

    while(true){
        char cwd[1024];
        char* current_dir=getcwd(cwd,sizeof(cwd));
        char* home=getenv("HOME");

        if(current_dir==nullptr){
            perror("getcwd");
            return 1;
        }
        string current=cwd;
        if(home!=nullptr){
        string home_dir=home;
        if(current.find(home_dir)==0){
            current.replace(0,home_dir.size(),"~");
        }
        }
        cout<<"Enma:"<<current<<">";
        getline(cin,input);
        if(input=="exit")break;
        //Split input into tokens (Break the input string into words to use it as commands)
        stringstream ss(input);
        vector<string>tokens;
        string token;

        while(ss>>token){
            tokens.push_back(token);
        }

        if(tokens.empty())continue;

            //handle Built int commands like cd
            if(tokens[0]=="cd"){
                if(tokens.size()<2){
                    cerr<<"cd: missing arguments \n";
                }

                else{
                //chdir(const char*path) change current working directory using path. Returns 0 success and 1 on failure
                //c_str() c++ to c style string
                    if(chdir(tokens[1].c_str())!=0){
                        perror("cd failed");
                    }
                }
                continue;

            }
            if(tokens[0]=="pwd"){
                char pwd[1024];
                char* present_dir=getcwd(pwd,sizeof(pwd));
                if(present_dir==nullptr){
                    perror("pwd");
                }
                else{
                cout<<present_dir<<endl;
                }
                continue;
            }

            if(tokens[0]=="help"){
                cout<<"Built-in commands:"<<endl;
                cout<<"cd <directory> - Change current directory to <directory>"<<endl;
                cout<<"pwd - Get present workind directory"<<endl;
                cout<<"exit- Exit from current terminal session"<<endl;
                continue;
            }
                      bool IO=false;
                      bool valid=true;

            string pathname;
              for(int i=0;i<tokens.size();i++){
                if(tokens[i]==">"){
                    //redirection
                    if(i+1<tokens.size()){
                    pathname=tokens[i+1];
                    IO=true;
                     tokens.erase(tokens.begin()+i,tokens.begin()+i+2);

                    }
                    else{
                        cerr<<"syntax error: expected filename after '>' "<<endl;
                        valid=false;
                    }
                }


                }

              if(!valid)continue;
            



        //converts vector of string into char*
        vector<char*>args;

        //for each token we have char* as pointer to it so we can use it for commands
        for(auto &str:tokens){
            args.push_back(&str[0]);
        }

        args.push_back(nullptr);//execvp needs last nullpointer aswell

        pid_t pid=fork();
        //create child and parent using fork
        
        if(pid==0){
            //child
            if(IO){
                 int fd=open(pathname.c_str(),O_TRUNC | O_WRONLY | O_CREAT , 0644);

                    if(fd==-1){
                        perror("open");
                        exit(1);
                    
                    }
                    else{
                        int newfd=dup2(fd,STDOUT_FILENO);
                        if(newfd==-1){
                            perror("dup2");
                            exit(1);
                        }
                        if(close(fd)==-1){
                            perror("close");
                            exit(1);
                        }
                    }
            }

            //args[0]is command which to execute and args.data is what arguments to pass to that program
            //like execvp("ls",{"ls","-l",nullptr});
            execvp(args[0],args.data());
            perror("command failed");//if fuction execvp fails
            exit(1);//exit child when execvp fail
        }
        else if(pid>0){
            //parent
            wait(nullptr);
        }
        else{

            perror("fork failed");
        }
    }
    return 0;
}

