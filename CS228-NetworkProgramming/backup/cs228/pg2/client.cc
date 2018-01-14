#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;
const int BUFSIZE=1024;

void Error(const char *msg,bool cond)
{	if(cond){
		perror(msg);
		exit(1);
	}
}

int MakeSocket(char *host, char *port) {
	int s; //file descriptor
	int len; //file descriptor
	struct sockaddr_in sa;//socket information
	struct hostent *hp; //host information
	struct servent *sp; //server informatino
	int portnum; //holds port number
	int ret;  //file descriptor

	hp = gethostbyname(host);
	Error("Gethostbyname",hp<0);
	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;
	sscanf(port, "%d", &portnum);
	if (portnum > 0) {
		sa.sin_port = htons(portnum);
	}
	else {
		sp=getservbyname(port, "tcp");
		Error("Error tcp",sp<0);
		portnum = sp->s_port;
		sa.sin_port = sp->s_port;
	}
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	Error("Socket not made",s<0);
	ret = connect(s, (struct sockaddr *)&sa, sizeof(sa));
	Error("No connection",ret<0);
	cout << "Connect to host " << host  << " port " << port << endl;
	return s;
}

main(int argc, char *argv[]) {


	int s;			//return value of Makesocket
	int len;		//return value for write and read
	char buf[BUFSIZE];	//char stream
	Error("No Port Supplied",argc<3);
	s = MakeSocket(argv[1], argv[2]);
	Error("Socket broke fool",s<0);

	int file=open("client.txt",O_RDONLY);
	Error("no open",file<0);
	int readLen=read(file,buf,BUFSIZE);
	while(readLen>0){
		cout << "Read " << readLen << endl;
		int w=write(s,buf,readLen);
		Error("write bad",w<0);
		readLen=read(file,buf,BUFSIZE);
	}
}



