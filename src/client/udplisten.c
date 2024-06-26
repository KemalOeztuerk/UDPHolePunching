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

#include "udplisten.h"

#define PORT "9999"


/*void *get_in_addr(struct sockaddr *sa){
   if(sa->sa_family == AF_INET)
     return &(((struct sockaddr_in*)sa)->sin_addr); // IPv4 address
   return &(((struct sockaddr_in6*)sa)->sin6_addr); // IPv6 address 
   }*/


void* start_udp_serv(){

  int sockfd;
  struct addrinfo hints, *servinfo, *p;
  int rv, numbytes;
  struct sockaddr_storage client_addr;
  char buf[INET6_ADDRSTRLEN];
  socklen_t addr_len;
  
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;      // use IPv4
  hints.ai_socktype = SOCK_DGRAM; // use UDP
  hints.ai_flags = AI_PASSIVE;    // use this machines ip;

  if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "getaddrinfo %s\n", gai_strerror(rv));
    pthread_exit((void *)-1);
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
    pthread_exit( (void*) 2 );
  }

  freeaddrinfo(servinfo);

  printf("udpserver is waiting for messages ...\n");


  while(1){

    printf("started to listen\n");
    addr_len = sizeof client_addr;
  if ((numbytes = recvfrom(sockfd, buf, INET6_ADDRSTRLEN-1 , 0, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
    perror("recvfrom");
    exit(1);
  }
  
   printf("NAT traversal working!!!!, buffer: %s  \n",buf);

   
  }

  close(sockfd);
  
 
  pthread_exit( (void*)0);
  
}


