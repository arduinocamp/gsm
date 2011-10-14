#ifndef QUECTELM10_H
#define QUECTELM10_H
#include <NewSoftSerial.h>
#include "GSM.h"

class QuectelM10 : public virtual GSM
{

  private:
    int configandwait(char* pin);
    int setPIN(char *pin);
    int changeNSIPmode(char);

  public:
    QuectelM10();
    ~QuectelM10();
    int start(char* pin=0);
    int restart(char* pin=0);
    int shutdown();
    int getCCI(char* cci);
	int getIMEI(char* imei);

    int sendSMS(const char* to, const char* msg);
    int attachGPRS(char* domain, char* dom1, char* dom2);
    boolean readSMS(char* msg, int msglength, char* number, int nlength);
    boolean readCall(char* number, int nlength);
    boolean call(char* number, unsigned int milliseconds);
    int dettachGPRS();
    int connectTCP(const char* server, int port);
    int disconnectTCP();
    int connectTCPServer(int port);
    boolean connectedClient();
    int write(const uint8_t* buffer, size_t sz);
	int write(uint8_t c);
    int write(const char* str);
	
    int read(char* result, int resultlength);
	uint8_t read();
    int readCellData(int &mcc, int &mnc, long &lac, long &cellid);
  
};

extern QuectelM10 gsm;

#endif

