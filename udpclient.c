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

#define SERVPORT "9999"


int main(int argc, char *argv[]){
  
 if (argc != 2) {
    fprintf(stderr,"usage: udpcli  hostname \n");
    exit(1);
  }
 
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

  if((rv = getaddrinfo(argv[1], SERVPORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "getaddrinfo %s\n", gai_strerror(rv));
    return 1;
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
    return -2;
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

  
  
  
  
 
  return 0;
  
}

