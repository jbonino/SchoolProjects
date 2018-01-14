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
#include <poll.h>

using namespace std;

const int BUFSIZE=1024;
struct pollfd clients[10];
string*name= new string[10];
int count=1;

void print(){
	cout<<"Current count: "<<count<<endl;
	for(int i=1;i<count;i++){
		cout<<"	Client "<<i<<" fd: "<<clients[i].fd<<endl;
	}
}

//server error
void error(const char *msg,bool cond)
{
	if(cond){
		perror(msg);
		exit(1);
	}
}
//client error
void cerror(bool cond,int i){
	if(cond){
		string a="Client "+name[i]+" has disconnected.\n";
		cout<<a;
		clients[i]=clients[count-1];
		name[i]=name[count-1];
		close(clients[i].fd);
		count--;
		for(int j=1;j<=count;j++){
			if(j!=i){
				int w=write(clients[j].fd,a.c_str(),a.length());
			}
		}
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

	char buf[BUFSIZE];

	error("No Port Provided",argc<2);

	int s = MakeServerSocket(argv[1]);
	error("Port Busy",s<0);
	struct sockaddr_in sa; //information of socket
	int sa_len = sizeof(sa); //get size of sockaddr_in
	error("ERROR sa",sa_len<0);

	clients[0].fd = s;
    clients[0].events = POLLIN;

	while(1){
		int ret=poll(clients, count, -1);
		if(ret>0){ //if anything on socket
			if(clients[0].revents & POLLIN){
				clients[count].fd = accept(s, (struct sockaddr *)&sa, (unsigned int *)&sa_len); //accept ther connection
				clients[count].events = POLLIN;
				error("client ERROR",clients[count].fd<0);
				cout<<"Client #"<<count<<" Connected"<<endl;

				char junk[10];
				sprintf(junk, "%d", count);//count to string

				name[count] = junk;
				count++;
				cout<<"after accept"<<endl;
			}
			else{ for(int i=1;i<count;i++){
				if(clients[i].revents & POLLIN){ //anything read
					cout<<"before read"<<endl;
					cout<<"Count is: "<<count<<endl;
					int r=read(clients[i].fd,buf,BUFSIZE-1);
					cout<<"after read"<<endl;
					cerror(r<1,i);
					buf[r]=0;
					string sbuff=string(buf);

					if(buf[0]=='/'){ //if special command
						if(buf[1]=='n'){ //change name
							sbuff=sbuff.substr(6,sbuff.length()-8); //grab just name
							string couter="Client "+name[i]+" changed nickname to "+sbuff+"\n"; //set string to cout and send to everyone
							cout<<couter;
							for(int j=1;j<count;j++) //write client changed name to everyone but self
	                            if(j!=i){
									int w=write(clients[j].fd,couter.c_str(),couter.length());
									cerror(w<1,j);
								}
							name[i]=sbuff; //change in name array to keep track of
						}
						if(buf[1]=='q'){ //if / followed by q. most likely quit
	                        cerror(true,i);
						}
					}
					else
						for(int j=1;j<count;j++){ //if not a special command then write to everyone
							if(j!=i){
								string a=name[i]+": "+sbuff;
								int w=write(clients[j].fd,a.c_str(),a.length());
								cerror(w<1,j);
							}
						}
					}
				}
		}
	}
}
}
