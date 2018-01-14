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
#include <string>

using namespace std;
const int BUFSIZE=1024;
char buf[BUFSIZE];

void error(const char *msg,bool cond)
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
	error("Gethostbyname",hp<0);
	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;
	sscanf(port, "%d", &portnum);
	if (portnum > 0) {
		sa.sin_port = htons(portnum);
	}
	else {
		sp=getservbyname(port, "tcp");
		error("Error tcp",sp<0);
		portnum = sp->s_port;
		sa.sin_port = sp->s_port;
	}
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	error("Socket not made",s<0);
	ret = connect(s, (struct sockaddr *)&sa, sizeof(sa));
	error("No connection",ret<0);
	cout << "Connect to host " << host  << " port " << port << endl;
	return s;
}

int s = MakeSocket((char*)"TRAVELLER.NMU.EDU",(char*) "25");


string get(string a){
	cout<<a;
	getline(cin,a);
	return a;
}

void writee(string a){
	int w=write(s,a.c_str(),a.length());
        error("write broke",w<0);
}
void reade(){
	int r=read(s,buf,1024);
	error("read broke",r<0);
	r=buf[0]-'0';
        error("helo broke",r>=4);


}

main(int argc, char *argv[]) {

	string a="HELO TRAVELLER.NMU.EDU \n";
	writee(a);
	reade();

	//FROM
	a=get("Who is mail from?: ");
	a="MAIL FROM:<"+a+"> \n";
	writee(a);
        reade();

	//SENDER
	a=get("Whom to send to?: ");
	a="RCPT TO:<"+a+"> \n";
	writee(a);
        reade();

	//DATA
	string b;
	cout<<"enter data: ";
	getline(cin,b);
	while(b!="."){
	getline(cin,b);
	a=a+"\n"+b;
	}
	a="DATA \n"+a+"\n.\n";
	writee(a);
        reade();

	cout<<"Message Success, press enter to exit"<<endl;
	getline(cin,a);
}



