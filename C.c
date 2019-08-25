
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>


int main(int argc, char *argv[]){
  char message[255];
  int server, n1,portNumber, pid, n;
  struct sockaddr_in servAdd;     // server socket address

 if(argc != 3){
    printf("Call model: %s <IP Address> <Port Number>\n", argv[0]);
    exit(0);
  }

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
     fprintf(stderr, "Cannot create socket\n");
     exit(1);
  }

  servAdd.sin_family = AF_INET;
  sscanf(argv[2], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);

  if(inet_pton(AF_INET, argv[1], &servAdd.sin_addr) < 0){
  fprintf(stderr, " inet_pton() has failed\n");
  exit(2);
}

 if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd))<0){
  fprintf(stderr, "connect() has failed, exiting\n");
  exit(3);
 }

read(server, message, 255);
fprintf(stderr, " %s\n", message);

 pid=fork();

  if(pid)
     while(1){                         /* reading server's messages */
       if(n=read(server, message, 255)){
          message[n]='\0';
          fprintf(stderr,"%s\n", message);
         }
	else{
		exit(0);
	}
}
  if(!pid)                   //         sending messages to server
    while(1){
      if(n=read(0, message, 255)){
         message[n]='\0';
         write(server, message, strlen(message)+1);
         if(!strcasecmp(message, "Quit\n")){
  		shutdown(server,2);
	//	close(server);
		kill(getpid(),SIGTERM);
          }
      }
}
}

