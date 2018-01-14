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

	int   sd;         //socket descriptor
   int    port;         //port number
   int   start;         //start port
   int    end;         //end port
   int    rval;         //socket descriptor for connect   
   struct hostent *hostaddr;   //To be used for IPaddress
   struct sockaddr_in servaddr;   //socket structure
	int s=0; //socket return value if connected properly
	int len; //file decriptor for read and write
	char buf[5]; //char stream
	sd = MakeServerSocket(argv[1]);

for(int i=1;i<1024;i++){
	memset( &servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(i); //set the portno
   memcpy(&servaddr.sin_addr, hostaddr->h_addr, hostaddr->h_length);
   rval = connect(sd, (struct sockaddr *) &servaddr, sizeof(servaddr));
   if(rval>0){
   printf("Port %d is open\n",port);
   close(sd);         //socket descriptor
   }
}
	/*
	while (1) {
		struct sockaddr_in sa; //information of socket
		int sa_len = sizeof(sa); //get size of sockaddr_in
		if(sa_len<0)error("ERROR sa");
		int fd = accept(s, (struct sockaddr *)&sa, (unsigned int *)&sa_len); //accept ther connection
		if(fd<0) error("fd ERROR"); 
		cout << "Connection:  ";
		cout << " address is " << (unsigned int)sa.sin_addr.s_addr;
		cout << " family " << sa.sin_family;
		cout << " port " << ntohs(sa.sin_port);
		cout << endl;
		while(1) {
			char buf2[BUFSIZE]; //new char stream
			len = read(fd, buf, BUFSIZE); //read and  return value to len
			if(len<1) error("Cannot read from socket");

			cout << "Read string \"" << buf << "\" length " << len << endl;
			sprintf(buf2, "%s LENGTH %d", buf, len);
			if(buf=="end")exit(1);
			len=write(fd, buf2, strlen(buf2));
			if(len<1) error("Cannot write to socket");
			cout << "Writing string \"" << buf2 << "\"" << endl;
		}
	}
	*/
}



