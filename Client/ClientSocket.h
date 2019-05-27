#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

class ClientSocket{
public:
	int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;


int createclient(char *argv[]) {

   portno = atoi(argv[2]);

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd == -1) {
      perror("ERROR opening client socket");
      return  -1;
   }

   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      return -1;
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   return 0;
}

int connecttoserver() {
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      return -1;
   }
   return sockfd;
}


};