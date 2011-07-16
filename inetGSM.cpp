#include "inetGSM.h"


int InetGSM::httpGET(const char* server, int port, const char* path, char* result, int resultlength)
{
  char itoaBuffer[8];
  int length_write;

  
  //Status = ATTACHED.
  if(gsm.getStatus()!=GSM::ATTACHED)
    return 0;
  
    
  if(!gsm.connectTCP(server, port))
    return 0;
 
  gsm.write((const uint8_t*)"GET ", 4);
  gsm.write((const uint8_t*)path, strlen(path));
  gsm.write((const uint8_t*)" HTTP/1.0\nHost: ", 16);
  gsm.write((const uint8_t*)server, strlen(server));
  gsm.write((const uint8_t*)"\n\n",2);

  
  int res= gsm.read(result, resultlength);

  gsm.disconnectTCP();
  
  return res;
}

int InetGSM::httpPOST(const char* server, int port, const char* path, const char* parameters, char* result, int resultlength)
{
  char itoaBuffer[8];
  int num_char;
  
  if (!gsm.connectTCP(server, port))
    return 0;

  
  strcpy(postbuffer,"POST ");
  strcat(postbuffer,path);
  strcat(postbuffer," HTTP/1.0\nHost: ");
  strcat(postbuffer,server);
  //  strcat(postbuffer,"\n\rUser-Agent: Mozilla/4.0\n\rContent-Length: ");
  strcat(postbuffer,"\nContent-Length: ");
  itoa(strlen(parameters),itoaBuffer,10);  
  strcat(postbuffer,itoaBuffer);
  strcat(postbuffer,"\n\n");
  strcat(postbuffer,parameters);
  strcat(postbuffer,"\n\n");
  
  
  
  gsm.write((const uint8_t*)postbuffer, strlen(postbuffer));


//  int res= gsm.read(result, resultlength);

  gsm.disconnectTCP();
  //return res;
   return 1;
}

int InetGSM::tweet(const char* token, const char* msg)
{
  //    gsm.httpPOST("arduino-tweet.appspot.com",80,"/update", "token=15514242-eWYAlMwjRQfrhnZxQiOfDXUpaYwjbSvMl1Nm5Qyg&status=Spam", buffer, 200);

  strcpy(tweetbuffer,"token=");
  strcat(tweetbuffer,token);
  strcat(tweetbuffer,"&status=");
  strcat(tweetbuffer, msg);
  httpPOST("arduino-tweet.appspot.com",80,"/update",tweetbuffer, tweetbuffer, BUFFERSIZE);
}

