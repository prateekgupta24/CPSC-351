#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

using namespace std;

int main(int argc, char*argv[])//allows the passing of command line arguments
{
  pid_t pid;
  int status;
  vector<string> url_list;
  ifstream input_file("urls.txt");
  string str;

  //Reading the File
  if(input_file.is_open())
  {
    while(getline(input_file, str))
    {
      url_list.push_back(str);
    }
    input_file.close();
  }
  else
  {
    cout << "File is not open\n";
  }
  //Creating new process
  pid = fork();

  //Iterating through the txt file
  for (int i = 0; i < url_list.size(); i++)
  {
    //if the fork returns negative value, creation of child process is unsuccesful
    if (pid == -1)
    {
      cout << ("Exiting.\n" );
      exit(1);
    }
    //if fork returns 0, new child process is created
    else if ( pid == 0 )
    {
      execlp("wget","-c", "-P", argv[2], url_list[i].c_str(), NULL);
      break;
    }
    //if fork returns a positive value(pid) of the child process to the parent.
    else
    {
      //wait for child process to terminate
      if (waitpid (pid, &status, 0 ) > 0)
           pid = fork();
    }
  }

  return 0;
}
