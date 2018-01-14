#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>

using namespace std;
const int BUFSIZE=102400;

void Error(const char *msg)
{
	perror(msg);
	exit(1);
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
	if (hp == 0)
		Error("Gethostbyname");
	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;
	sscanf(port, "%d", &portnum);
	if (portnum > 0) {
		sa.sin_port = htons(portnum);
	}
	else {
		sp=getservbyname(port, "tcp");
		if(sp<0) Error("Error tcp");
		portnum = sp->s_port;
		sa.sin_port = sp->s_port;
	}
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	if(s<0) Error("Socket not made");
	ret = connect(s, (struct sockaddr *)&sa, sizeof(sa));
	if(ret<0) Error("No connection");
	cout << "Connect to host " << host  << " port " << port << endl;
	return s;
}

main(int argc, char *argv[]) {


	int s;			//return value of Makesocket
	int len;		//return value for write and read
	char buf[BUFSIZE];	//char stream
	s = MakeSocket(argv[1], argv[2]);
	if(s<0) Error("Socket broke fool");
	while(1) { //run till broke
		cout << "Enter a line for the server\n";
		cout<<endl;
		cin.getline(buf, BUFSIZE); //input text
		len = write(s, buf, strlen(buf)+1); //write to socket
		if(len<1) Error("Could Not Write"); //if error writing
		cout << "Wrote " << len << " bytes " << endl; //print
		len = read(s, buf, BUFSIZE-1); //read 
		if(len<1) Error("Could Not Read");//if error reading
		buf[len] = 0; 
		if(buf[0]=='e'&&buf[1]=='n'&&buf[2]=='d')	exit(0); //if end then exit
		cout << "server says\n";
		cout << buf; //print buf
	}
}



