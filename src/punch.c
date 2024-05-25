
#include <stdio.h>
#include <pthread.h>
#include "udpcli.h"
#include "udpserv.h"

int main(int argc, char* argv[]){


  if(argc != 2){
    printf("usage: punch hostname\n");
    return -1;
  }
  pthread_t cli_thread,serv_thread;

  if( pthread_create(&cli_thread, NULL, start_udp_cli, (void*)argv[1]) != 0){
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
