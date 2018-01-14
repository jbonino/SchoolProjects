#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

char *lsCmd[] = { "ls", "-l", NULL };
char *psCmd[] = { "ps", "aux", NULL };
char *grepCmd[] = { "grep", "root", NULL };

void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

void setDeadChildHandler(){
	struct sigaction sigact;

	sigact.sa_handler = sigchld_handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_RESTART;
	if( sigaction(SIGCHLD, &sigact, NULL) == -1){
		fprintf(stderr, "Could not set SIGCHLD handler.\n");
		exit(-1);
	}
}

pid_t forkCommand( char *argv[] ){
	pid_t ret=fork();
	if(ret<0){exit(EXIT_FAILURE); return -1;} //error

	if(ret==0){ //child
		pid_t exec=execvp(*argv,argv);
		if(exec<0){exit(EXIT_FAILURE); return 1;}
	}

	return pid_t;
}

pid_t forkCommandRedirect( char *argv[], int fds[] ){
	pid_t  ret;
    
	ret=fork();
    if (ret < 0) {exit(EXIT_FAILURE);return-1;}
    else if (pid == 0) { //child
        for(int i = 0; i < 3; i++){
            if(fds[i] != -1){
                dup2(fds[i], i);
                close(fds[i]);
            }
        }
		pid_t exec = execvp(*argv,argv);
        if (exec<0) { exit(EXIT_FAILURE);return -1;}

    }
    return ret;
	
}

void samplePipeline(){
	pid_t	cmdPid, deadPid;
	int		pipeFds[2];
	int		proc1Fds[3] = {-1, -1, -1};
	int		proc2Fds[3] = {-1, -1, -1};

	setDeadChildHandler();
	if( pipe(pipeFds) < 0 ){
		fprintf( stderr, "Pipe error\n" );
		exit(1);
	} 
	proc1Fds[1] = pipeFds[1];
	proc2Fds[0] = pipeFds[0];
	cmdPid = forkCommandRedirect( psCmd, proc1Fds );
	cmdPid = forkCommandRedirect( grepCmd, proc2Fds );
	close(pipeFds[0]);
	close(pipeFds[1]);
}

int main(int argc, char *argv[]){
	if( argc > 1 ){
		int status;
		if( forkCommand( &argv[1] ) > 0 )
			wait(&status);
	} else {
		samplePipeline();
	}
	return 0;
}