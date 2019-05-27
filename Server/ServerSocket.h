#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

#define BUFFER_SIZE 256
class ServerSocket{
	public:
		
		struct sockaddr_storage cli_addr;
		int socketfd, clifd, flag, optval,BACKLOG;
		socklen_t addrlen, clilen;
		struct addrinfo hints;
		struct addrinfo *result, *rp;		//rp is just a temp variable for later
		#define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
		char addrStr[ADDRSTRLEN];
		char host[NI_MAXHOST];
		char service[NI_MAXSERV];
		const char* errstr[];

		
		int createServerSocket(const char *host, const char *service) {

			memset(&hints, 0, sizeof(struct addrinfo));
			hints.ai_canonname = NULL;
			hints.ai_addr = NULL;
			hints.ai_next = NULL;
			hints.ai_family = AF_UNSPEC;		/* Allows IPv4 or IPv6 */
			hints.ai_socktype = SOCK_STREAM;
			flag = getaddrinfo(host, service, &hints, &result);
			if (flag!=0)
				printf("ERROR getting addrinfo structure\n");
			
			/* Walk through returned list until we find an address structure
			that can be used to successfully connect a socket */
			for (rp = result; rp != NULL; rp = rp->ai_next) {
				socketfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
				if (socketfd == -1)
					continue;			/* On error, try next address */
				
				optval = 0;
				if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
					printf("error setting SO_REUSEADDR option for socket\n");
				
				if (bind(socketfd, rp->ai_addr, rp->ai_addrlen) == 0) {
					printf("bound successfully\n");
					break;
				}
				close(socketfd);				/* Connect failed: close this socket and try next address */
			}

			freeaddrinfo(result);

			if (socketfd==-1)
				printf("Unable to create socket\n");
			return (rp == NULL) ? -1 : socketfd;
			
		}

		int listentoport(int BACKLOG) {
		   	if(listen(socketfd, BACKLOG)==-1) {
		   			printf("listen ERROR\n");
		   			//return -1;
		   			exit(1);
		   		} 
		   	printf("port set as litening port\nListening.......\n");
		      while(1) {
		   		

		   		clifd = accept(socketfd, (struct sockaddr *) &cli_addr, &clilen);
		   		//printf("%d\n",clifd );
		   		if (clifd < 0) {
		   			printf("ERROR on accept\n");
		   			//perror("ERROR on accept");
		   			return -1;
		   		}
		       	else 
		       		break;
		   	}
		   	
		   	return clifd;

		}



};