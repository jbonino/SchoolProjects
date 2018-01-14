#include <iostream>		// cout, cerr, etc
#include <stdio.h>		// perror
#include <string.h>		// bcopy
#include <netinet/in.h>		// struct sockaddr_in
#include <unistd.h>		// read, write, etc
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>

using namespace std;

const int BUFSIZE=1024;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int MakeServerSocket(char *port) {
	const int MAXNAMELEN = 255; //max length of buffer
	const int BACKLOG = 3; //connections to socket
	char localhostname[MAXNAMELEN]; //stream of chars
	int s; //file descriptor
	int len; //file descriptor
	struct sockaddr_in sa; //socket address information
	struct hostent *hp; //host info
	struct servent *sp; //server info
	int portnum; //port num
	int ret; //file decriptor

	gethostname(localhostname,MAXNAMELEN);
	hp = gethostbyname(localhostname);
	if(hp==NULL)error("hp is null");
	sscanf(port, "%d", &portnum);
	if (portnum ==  0) {
		sp=getservbyname(port, "tcp");
		portnum = ntohs(sp->s_port);
	}
	sa.sin_port = htons(portnum);

	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;

	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	if(s<0) error("Socket ERROR");
	ret = bind(s, (struct sockaddr *)&sa, sizeof(sa));
	if(s<0) error("Bind ERROR");
	listen(s, BACKLOG);
	cout << "Waiting for connection on port " << port << " hostname " << localhostname << endl;
	return s;
}

int main(int argc, char *argv[]) {


	int s; //socket return value if connected properly
	int len; //file decriptor for read and write
	char buf[BUFSIZE]; //char stream

	s = MakeServerSocket(argv[1]);
	if(s<0) error("Port Busy");

	
		struct sockaddr_in sa; //information of socket
		int sa_len = sizeof(sa); //get size of sockaddr_in
		if(sa_len<0)error("ERROR sa");
		int fd = accept(s, (struct sockaddr *)&sa, (unsigned int *)&sa_len); //accept ther connection
		if(fd<0) error("fd ERROR"); 
		
			len = read(fd, buf, BUFSIZE); //read and  return value to len
			if(len<1) error("Cannot read from socket");
			while(len>0){
				char junk[10];
                                sprintf(junk, "%d", len);
				string length=string(junk);
				write(fd,length.c_str(),length.length());
				cout<<"read "<<buf<<endl;
				len=read(fd,buf,BUFSIZE);
			
	
}
}



