#include "inetGSM.h"


int InetGSM::httpGET(const char* server, int port, const char* path, char* result, int resultlength)
{
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

  
  strcpy(_buffer,"POST ");
  strcat(_buffer,path);
  strcat(_buffer," HTTP/1.0\nHost: ");
  strcat(_buffer,server);
  //  strcat(_buffer,"\n\rUser-Agent: Mozilla/4.0\n\rContent-Length: ");
  strcat(_buffer,"\nContent-Length: ");
  itoa(strlen(parameters),itoaBuffer,10);  
  strcat(_buffer,itoaBuffer);
  strcat(_buffer,"\n\n");
  strcat(_buffer,parameters);
  strcat(_buffer,"\n\n");
  
  
  
  gsm.write((const uint8_t*)_buffer, strlen(_buffer));


//  int res= gsm.read(result, resultlength);

  gsm.disconnectTCP();
  //return res;
   return 1;
}

int InetGSM::tweet(const char* token, const char* msg)
{
  //    gsm.httpPOST("arduino-tweet.appspot.com",80,"/update", "token=15514242-eWYAlMwjRQfrhnZxQiOfDXUpaYwjbSvMl1Nm5Qyg&status=Spam", buffer, 200);

  strcpy(_buffer,"token=");
  strcat(_buffer,token);
  strcat(_buffer,"&status=");
  strcat(_buffer, msg);
  httpPOST("arduino-tweet.appspot.com",80,"/update",_buffer, _buffer, BUFFERSIZE);
}

int InetGSM::openmail(char* server, char* loginbase64, char* passbase64, char* from, char* to, char* subj)
{
	  if (!gsm.connectTCP(server, 25))
    	return 0;
    
    delay(1000);
    gsm.read(_buffer, BUFFERSIZE);    
    gsm.write("HELO\n");
    delay(500);
    gsm.read(_buffer, BUFFERSIZE);
    gsm.write("AUTH LOGIN\n");
    delay(500);
    gsm.read(_buffer, BUFFERSIZE);
    gsm.write(loginbase64);gsm.write("\n");
    delay(500);
    gsm.read(_buffer, BUFFERSIZE);
    gsm.write(passbase64);gsm.write("\n");
    delay(500);
    gsm.read(_buffer, BUFFERSIZE);
    gsm.write("MAIL FROM: ");gsm.write(from);gsm.write("\n");
    delay(500);
    gsm.read(_buffer, BUFFERSIZE);
    gsm.write("RCPT TO: ");gsm.write(to);gsm.write("\n");
    delay(500);
    gsm.read(_buffer, BUFFERSIZE);
    gsm.write("Subject: ");gsm.write(subj);gsm.write("\n\n");
    return 1;
}
int InetGSM::closemail()
{
	gsm.write("\n.\n");
	gsm.disconnectTCP();
	return 1;
}
 