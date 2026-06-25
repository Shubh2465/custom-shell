#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<vector>
#include<sstream>
#include<cstring>
using namespace std;
int main(){
    string input;

    while(true){
        cout<<"Enma-Shell>";
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

