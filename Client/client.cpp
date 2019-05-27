#include "ClientSocket.h"

int main(int argc, char *argv[]) {
	int socketfd, connstat;
	ssize_t readnum, writenum;
	char buffer[256];
	ClientSocket clientSocket;
	if (argc < 3) {
      fprintf(stderr,"usage:  %s hostname port\n", argv[0]);
      return -1;
    }

	socketfd = clientSocket.createclient(argv);
	//printf("%d\n",socketfd );
	if (socketfd != -1) {
		printf("client socket created\n");
		socketfd = clientSocket.connecttoserver();
		//printf("%d\n",socketfd );
		if (socketfd==-1) {
			printf("Error connecting to server\n");
			exit(1);
		}
		if(read(socketfd, buffer, sizeof(buffer)) != 0)
				printf("%s\n",buffer );
		while (1){
			bzero(buffer,256);
			
				//write(STDOUT_FILENO, &buffer, sizeof(buffer));
			//bzero(buffer,256);
			fgets(buffer,255,stdin);
			writenum = write(socketfd,(void *) buffer, sizeof(buffer));
			//if (writenum!=0)
			//	printf("%s\n", buffer);
				//writenum = write(socketfd,(void *) buffer, sizeof(buffer));
			
			
			//writenum = write(STDOUT_FILENO, buffer, sizeof(buffer));
			
		}
	}
	return 0;
}