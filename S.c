
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void serviceClient(int);
int main(int argc, char *argv[]){
  int i, sd, client, portNumber, status;
  struct sockaddr_in servAdd;      // client socket address

 if(argc != 2){
    printf("Call model: %s <Port Number>\n", argv[0]);
    exit(0);
  }
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "Cannot create socket\n");
    exit(1);
  }
  sd = socket(AF_INET, SOCK_STREAM, 0);
  servAdd.sin_family = AF_INET;
  servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
  sscanf(argv[1], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);

  bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
  listen(sd, 5);

 i=0;
  while(1){
    i++;
    printf("Waiting for a client :)\n");
    client = accept(sd, NULL, NULL);
    printf("Got client %d \n",i);

    if(!fork())
      serviceClient(client);

     close(client);
     waitpid(0, &status, WNOHANG);

 }
//   close(client);
 //   waitpid(0, &status, WNOHANG);

}
void serviceClient(int sd){
	char message[255],*arg[10],*saveptr1, *saveptr2,*saveptr3,*a,*or="||",*and="&&";
        char *c,*b,*pos;
        int status,n1,i=0,j,flag,f,n;
        pid_t pid;

	dup2(sd,0);
	dup2(sd,1);
	dup2(sd,2);
	write(sd, "Write commands to execute", 50);
	while(1){

	n= read(sd, message, 255);
		if(n<0)
		{
 			fprintf(stderr, "Bye, client \n");
			exit(0);
		}

		pos=strtok(message,"\n");
		c=strtok_r(pos,";",&saveptr1);

		while(c != NULL){
			arg[0]="program";
			if(strstr(c,or)!=NULL)
				flag=1;
		if(strstr(c,and)!=NULL)
			flag=0;

		if( (strstr(c,or)!=NULL) || (strstr(c,and)!=NULL) )
		{
			b=strtok_r(c,"||&&",&saveptr3);
			while(b!=NULL){
				a=strtok_r(b," ",&saveptr2);
				j=1;
        	       		while(a!=NULL){
      			        	arg[j]=a;
              				a=strtok_r(NULL," ",&saveptr2);
                       			j++;
				}
                		arg[j]=NULL;

				pid=fork();
				if(!pid){
                        		if(execvp(arg[1],&arg[1])==-1){
                              			fprintf(stderr,"Command not found");
						if(flag==0)
                                                	exit(4);
					}
				}
				else{
		 			waitpid(pid, &status, 0);

		                	if(WIFEXITED(status))
               	 			{
                	        		int exit_status = WEXITSTATUS(status);
						if(exit_status==0 && flag==1)
							exit(4);
						if(exit_status!=0 && flag==0)
						exit(4);
					}
				}
				b=strtok_r(NULL,"||&&",&saveptr3);
			}
	}
	else{
		a=strtok_r(c," ",&saveptr2);

		j=1;
		while(a!=NULL){
			arg[j]=a;
			a=strtok_r(NULL," ",&saveptr2);
			j++;
		}
		arg[j]=NULL;

		pid=fork();
		if(!pid){
			if(execvp(arg[1],&arg[1])==-1)
				fprintf(stderr,"Command not found");
		}
		else{
	    		waitpid(pid, &status, 0);
			if(WIFEXITED(status))
	                {
                        	int exit_status = WEXITSTATUS(status);
		}
		}
	}

	memset(arg, 0, sizeof(arg));
	c = strtok_r(NULL,";",&saveptr1);

	}

	}
}

