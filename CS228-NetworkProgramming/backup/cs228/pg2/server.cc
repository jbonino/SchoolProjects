#include <iostream>		// cout, cerr, etc
#include <stdio.h>		// perror
#include <string.h>		// bcopy
#include <netinet/in.h>		// struct sockaddr_in
#include <unistd.h>		// read, write, etc
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

const int BUFSIZE=1024;

void error(const char *msg,bool cond)
{
	if(cond){
		perror(msg);
		exit(1);
	}
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
	error("hp is null",!hp);
	sscanf(port, "%d", &portnum);
	if (portnum ==  0) {
		sp=getservbyname(port, "tcp");
		portnum = ntohs(sp->s_port);
	}
	sa.sin_port = htons(portnum);

	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;

	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	error("Socket ERROR",s<0);
	ret = bind(s, (struct sockaddr *)&sa, sizeof(sa));
	error("Bind ERROR",ret<0);
	listen(s, BACKLOG);
	cout << "Waiting for connection on port " << port << " hostname " << localhostname << endl;
	return s;
}

int main(int argc, char *argv[]) {


	int s; //socket return value if connected properly
	int len; //file decriptor for read and write
	char buf[BUFSIZE]; //char stream
	error("No Port Provided",argc<2);
	s = MakeServerSocket(argv[1]);
	error("Port Busy",s<0);


	struct sockaddr_in sa; //information of socket
	int sa_len = sizeof(sa); //get size of sockaddr_in
	error("ERROR sa",sa_len<0);
	int fd = accept(s, (struct sockaddr *)&sa, (unsigned int *)&sa_len); //accept ther connection
	error("fd ERROR",fd<0);
	cout << "Connection:  ";
	cout << " address is " << (unsigned int)sa.sin_addr.s_addr;
	cout << " family " << sa.sin_family;
	cout << " port " << ntohs(sa.sin_port);
	cout << endl;

	int file=open("text.txt", O_WRONLY | O_CREAT | O_TRUNC,  0666);
	error("Cant open",file<0);
	int readLen = read(fd, buf, BUFSIZE);
	while(readLen>0){
		cout << "Read " << readLen << endl;
		int a = write(file, buf, readLen);
		error("writes broke fool/hung up",a<0);
		readLen = read(fd, buf, BUFSIZE);
	}
}



