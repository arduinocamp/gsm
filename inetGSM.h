#ifndef _INETGSM_H_
#define _INETGSM_H_

#define BUFFERSIZE 200

#include "QuectelM10.h"

class InetGSM
{
  private:
    char tweetbuffer[BUFFERSIZE];
    char postbuffer[BUFFERSIZE];
    
  public:
    int httpGET(const char* server, int port, const char* path, char* result, int resultlength);
    int httpPOST(const char* server, int port, const char* path, const char* parameters, char* result, int resultlength);
    int tweet(const char* token, const char* msg);

};

#endif
