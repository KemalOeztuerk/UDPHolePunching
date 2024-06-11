
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>


typedef struct hostinfo_t {
  char hostname[INET6_ADDRSTRLEN];
  unsigned short port;
}hostinfo;


int main(int argc, char* argv[]){
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <PORT>\n", argv[0]);
    return 1;
  }

  char *PORT = argv[1];
  int sockfd;
  struct addrinfo hints, *servinfo, *p;
  int rv, numbytes;

  //client info
  struct sockaddr_storage client_addr;
  socklen_t addr_len;
  char buf[INET6_ADDRSTRLEN];
  hostinfo *hi = malloc(sizeof(hostinfo));

  
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;

  if((rv = getaddrinfo(NULL,PORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "getaddrinfo %s\n", gai_strerror(rv));
    exit(-1);
  }

  for(p=servinfo; p!=NULL; p = p->ai_next){
    if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("server: socket\n");
      continue;
    }

    if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
      perror("udpsever: bind\n");
      continue;
    }
    break;
  }

  if(p == NULL){
    fprintf(stderr, "udpserver: failed to bind socket\n");
    exit(-1);
  }

  freeaddrinfo(servinfo);

  printf("server is listening...\n");

  while(1){

    printf("started to listen\n");
    addr_len = sizeof client_addr;
  if ((numbytes = recvfrom(sockfd, buf, INET6_ADDRSTRLEN-1 , 0, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
    perror("recvfrom");
    exit(1);
  }

  // Get the client's IP address and port
        if (client_addr.ss_family == AF_INET) { // IPv4
            struct sockaddr_in *s = (struct sockaddr_in *)&client_addr;
            inet_ntop(AF_INET, &s->sin_addr, hi->hostname, sizeof hi->hostname);
            hi->port = s->sin_port;
        } else { // IPv6
            struct sockaddr_in6 *s = (struct sockaddr_in6 *)&client_addr;
            inet_ntop(AF_INET6, &s->sin6_addr, hi->hostname, sizeof hi->port);
            hi->port = s->sin6_port;
        }

	
	
	if(sendto( sockfd, hi, sizeof(hostinfo), 0,p->ai_addr , p->ai_addrlen)==-1){
	  perror("sendto");
	  exit(-1);
	}
  
	printf("Client address: %s, Client port:%d\n",hi->hostname, hi->port);
	printf("Message: %s\n", buf);


   
  }

  close(sockfd);
  
  return 0;
}
