#include "ServerSocket.h"
#define ADDRESS_SIZE 128
#define BUFFER_SIZE 256
int main() {
	int clientfd, n;
	char buffer[BUFFER_SIZE];
	char address[2][ADDRESS_SIZE] = {"localhost", "9099"};
	char welcome[] = {"you have successfully conncted\n"};
	ServerSocket serverSocket;
	if (serverSocket.createServerSocket(address[0], address[1]) == 0)
		printf("successfully connected\n");


	clientfd = serverSocket.listentoport(5);
	if (clientfd==-1)
		exit(1);
	else if (clientfd != -1) {
		write(clientfd, welcome, sizeof(welcome));
		printf("client connected!\n");
	}
	while(1) {
		bzero(buffer,256);
		n = read(clientfd, buffer, sizeof(buffer));
		
		if (n==0){
			printf("client terminated.\nserver shutting off!\n");
			break;
		}
		else
			printf("%s\n",buffer );
			
		

	}
	return 0;
}