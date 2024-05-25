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

#define SERVPORT "9999"



void *start_udp_cli(void *args){

  char *host = (char*) args;
  int sockfd;
  struct addrinfo hints, *servinfo, *p;
  int rv, numbytes;
  //char buf[INET6_ADDRSTRLEN]; // size is not important now
  socklen_t addr_len;
  // char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;      // use IPv4
  hints.ai_socktype = SOCK_DGRAM; // use UDP
  //hints.ai_flags = AI_PASSIVE;    // use this machines ip;

  if((rv = getaddrinfo(host, SERVPORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "getaddrinfo %s\n", gai_strerror(rv));
    pthread_exit( (void *) -1);
  }


  for(p=servinfo; p!=NULL; p = p->ai_next){
    if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("udpclient: socket\n");
      continue;
    }

    /* if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
      perror("udpclient: bind\n");
      continue;
      }*/
    break;
  }

  if(p == NULL){
    fprintf(stderr, "udpclient: failed to bind socket\n");
    pthread_exit( (void*) -2);
  }

  freeaddrinfo(servinfo);

  printf("udpclient is waiting for messages ...\n");



  char msg[1024] = "some message"; 
  while(1){
    
  if((numbytes = sendto(sockfd, msg, 1024, 0, p->ai_addr, p->ai_addrlen)) == -1){
    perror("sendto");
    break;
    exit(1);
  }
  
  sleep(1);

  printf("sent a packet!!!\n");
 
  
  }

  close(sockfd);

  pthread_exit( (void *) 0);
  
}


