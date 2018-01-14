#include <iostream>		// cout, cerr, etc
#include <stdio.h>		// perror
#include <string.h>		// bcopy
#include <sstream>
#include <netinet/in.h>		// struct sockaddr_in
#include <unistd.h>		// read, write, etc
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

using namespace std;

const int BUFSIZE=1024;


void error(const char *msg,bool cond){
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


void parser(string buf,string& get,string& filename, string& version ){
	istringstream is (buf);
	is >> get;
	is >> filename;
	if(filename.length()>1)
		filename=filename.substr(1);
	is >> version;
}

void doWrite(string metadata,string filename,int client){
	char buf[BUFSIZE];
	string version=metadata;
	//get type
	int period=filename.find('.');
	string type=filename.substr(period+1);

	if(type=="jpeg") type="image/"+type;
	else type="text/html";
	metadata="\n"+version+" 200 OK"+"\n"+"Content-Type: "+type;
	metadata=metadata.substr(1);
	if(version!="HTTP/0.9"){
		//write metadata
		int wrote=write(client,metadata.c_str(),metadata.length());
		error("Bad Meta Write",write<0);
		metadata="\n\n";
		//write blank space so meta done
		wrote =write(client,metadata.c_str(),metadata.length());
		error("Bad Meta Write",write<0);
	}

	//if file exists and in dir
	cout<<"filename: '"<<filename<<"'"<<endl;
	int fileopen=open(filename.c_str(), O_RDONLY);
	error("File Not Found",fileopen<0);
	int reader=read(fileopen,buf, BUFSIZE);
	while(reader>0){
		cout<<buf<<endl;
		int a = write(client, buf, reader);
		error("writes broke fool",a<0);
		reader = read(fileopen, buf, BUFSIZE);
	}
}
string writelog(string buf){
	string log;

	//time shit
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime (buffer,80,"[%d/%b/%Y:%X +100]",timeinfo);
	string datime(buffer);

	log="computer - -"+datime+" "+buf+"\n";
	return log;
}

int main(int argc, char *argv[]) {
	//socket stuff
	error("No Port Provided",argc<2);
	int s = MakeServerSocket(argv[1]);
	error("Port Busy",s<0);
	struct sockaddr_in sa; //information of socket
	int sa_len = sizeof(sa); //get size of sockaddr_in
	error("ERROR sa",sa_len<0);


	//open logfile
	int log=open("logfile", O_WRONLY | O_CREAT, 0660);
	error("bad log",log<0);

	//declare variables
	char buf[BUFSIZE]; //char stream
	string get, filename, version, metadata;
	while(1){
		//accept
		int client = accept(s, (struct sockaddr *)&sa, (unsigned int *)&sa_len); //accept ther connection
		error("client ERROR",client<0);
		//forking
		int pid=fork();
		error("fork wrong fool",pid<0);

		//child
		if(pid==0){

			//get what client sent
			int r=read(client,buf,4000);
			error("Bad Read",r<0);
			string buffer(buf,r);
			parser(buf,get,filename,version);
			if(filename[0]=='~'){
				filename=filename.substr(1);
				int sla=filename.find('/');
				string na=filename.substr(0,sla);
				filename=filename.substr(sla+1);
				filename="home/"+na+"/pub/"+filename;
			}
			//close if internet explorer
			int ie=buffer.find("Trident/");
			error("Internet Explorer bad",ie>0);

			//logging
			string logger=writelog(get+"/ "+filename+"/ "+version);
			int writer=write(log,logger.c_str(),logger.length());
			error("bad write",writer<0);

			//check version
			if(version=="HTTP/0.9"){
				//write to client
				doWrite(version,filename,client);
				//close socket
				close(s);
			}
			else if(version=="HTTP/1.0"){
				//write to client
	                	doWrite(version,filename,client);
				close(s);
			}
			else{
				//write to client
	                doWrite(version,filename,client);

			//else close(s);
			}
			exit(1);
		}
	else{
		int w;
		int status;
		do{ w=waitpid(-1, &status, WNOHANG); }
		while (w>0);


	}
}
}