#include "tsh.h"

using namespace std;

void simple_shell::parse_command(char* cmd, char** cmdTokens) {
  // TODO: tokenize the command string into arguments
  if (cmd)
  {
    int i = 0 ;
    char s[2]=" ";
    char * token = strtok(cmd,s);
    while(token!= NULL)
    {
      i++ ;
      cmdTokens[i] = token;
      token = strtok(NULL, s);
    }
    for (int j =0 ; cmdTokens[i][j]!='\0'; j++)
      {
        if(cmdTokens[i][j]=='\n')
        {
          cmdTokens[i][j]='\0' ; 
        }
      }
   cmdTokens[i+1]= NULL;
  }
  else 
  {
    return ;
  }

}

void simple_shell::exec_command(char **argv)
{
  // TODO: fork a child process to execute the command.
  // parent process should wait for the child process to complete and reap it
  int fs =fork();
  if (fs==0){
    execvp(argv[0],argv);
  }
  else if (fs<0){
    cout<<"error in forking";
    exit(1);
  }
  else{
    wait (NULL);
  }
}

bool simple_shell::isQuit(char *cmd){
  // TODO: check for the command "quit" that terminates the shell
return (strcmp(cmd, "quit") == 0);

}
