#ifndef UDPSEND_H
#define UDPSEND_H

#include <netinet/in.h>


typedef struct hostinfo_t {
  char hostname[INET6_ADDRSTRLEN];
  unsigned short port;
}hostinfo;

void *start_send(void *args);

#endif
