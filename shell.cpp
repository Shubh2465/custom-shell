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
        cout<<"myshell>";
        getline(cin,input);
        if(input=="exit")break;
        //Split input into tokens
        stringstream ss(input);
        vector<string>tokens;
        string token;

        while(ss>>token){
            tokens.push_back(token);
        }

        if(tokens.empty())continue;

        //converts vector of string into char*

        vector<char*>args;
        for(auto &str:tokens){
            args.push_back(&str[0]);
        }
        args.push_back(nullptr);

        pid_t pid=fork();
        if(pid==0){
            //child
            execvp(args[0],args.data());
            perror("command failed");
            exit(1);
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

