
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "udpsend.h"
#include "udplisten.h"

int main(int argc, char* argv[]){


  if(argc != 3){
    printf("usage: punch hostname port\n");
    return -1;
  }
  pthread_t cli_thread,serv_thread;
  
  //set host info
  hostinfo *hi = malloc(sizeof(hostinfo));
  //set hostname
  memcpy(hi->hostname,argv[1], strlen(argv[1])+1 );
  //set port
  hi->port = (unsigned short)atoi(argv[2]);

  if( pthread_create(&cli_thread, NULL, start_send, (void*)hi) != 0){
      fprintf(stderr, "Failed to create client thread\n");
      return -1;
    }

  if( pthread_create(&serv_thread, NULL, start_udp_serv, NULL) != 0 ){
      fprintf(stderr, "Failed to create server thread\n");
      return -1;
    }

  pthread_join(cli_thread,NULL);
  pthread_join(serv_thread, NULL);
      
  return 0;
}
