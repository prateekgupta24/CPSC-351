File downloaders are programs used for downloading ﬁles from the Internet. In this assignment you will implement two diﬀerent types of multi-process downloaders (i.e., ﬁle downloaders that comprise multiple processes):

  1. a serial ﬁle downloader which downloads ﬁles one by one.

You will then compare the performance of the two types of downloaders. Both downloaders will use the Linux wget program in order to perform the actual downloading. The usage of the wget is simple: wget <FILE URL>. For example, running from command line the following command:

  wget http://releases.ubuntu.com/16.04/ubuntu-16.04.6-desktop-amd64.iso.zsync

will download the Ubuntu Linux iso image to the current directory. Before proceeding with the assignment, you may want to take a moment to experiment with the wget command.
In your program, the parent process shall ﬁrst read the ﬁle, urls.txt, containing the URLs of the ﬁles to be downloaded. urls.txt shall have the following format:

  " <URL1> <URL2> . . . "
  
For example:

  http://releases.ubuntu.com/16.04/ubuntu-16.04.6-server-amd64.iso
  http://releases.ubuntu.com/16.04/ubuntu-16.04.6-server-i386.iso

Next, the parent process shall fork the child processes. Each created child process shall use the execlp() system call to replace its executable image with that of the wget program.

The serial downloader program shall be called serial.cpp.

The serial downloader shall download ﬁles one by one. After the parent process has read and parsed the urls.txt ﬁle, it shall proceed as follows:

  1. The parent process forks oﬀ a child process.
  2. The child uses execlp("/usr/bin/wget", "wget", <URL STRING1>, NULL) system call in order to replace its program with wget program that will download the ﬁrst ﬁle in urls.txt (i.e. the ﬁle at URL <URL STRING1>).
  3. The parent executes a wait() system call until the child exits.
  4. The parent forks oﬀ another child process which downloads the next ﬁle speciﬁed in urls.txt.
  5. Repeat the above steps until all ﬁles are downloaded.
