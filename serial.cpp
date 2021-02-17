/*
CPSC 351-04
Prateek Gupta
02-19-2021
CWID: 888625282
Program 2 - Serial Downloader
1. The parent process forks oﬀ a child process.
2. The child uses execlp("/usr/bin/wget", "wget", <URL STRING1>, NULL)
   system call in order to replace its program with wget program that will download
   the ﬁrst ﬁle in urls.txt (i.e. the ﬁle at URL <URL STRING1>).
3. The parent executes a wait() system call until the child exits.
4. The parent forks oﬀ another child process which downloads the next ﬁle speciﬁed in urls.txt.
5. Repeat the above steps until all ﬁles are downloaded.
*/

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
