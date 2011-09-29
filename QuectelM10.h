#ifndef QUECTELM10_H
#define QUECTELM10_H
#include <NewSoftSerial.h>
#include "GSM.h"

class QuectelM10 : public virtual GSM
{

  private:
    int configandwait(char* pin);

  public:
    QuectelM10();
    ~QuectelM10();
    int start(char* pin=0);
    int restart(char* pin=0);
    int shutdown();
    int sendSMS(const char* to, const char* msg);
    int attachGPRS(char* domain, char* dom1, char* dom2);
    boolean availableSMS();
    boolean readSMS(char* msg, int msglength, char* number, int nlength);
    boolean readCall(char* number, int nlength);
    boolean call(char* number, unsigned int milliseconds);
    int dettachGPRS();
    int connectTCP(const char* server, int port);
    int disconnectTCP();
    int connectTCPServer(int port);
    boolean connectedClient();
    int write(const uint8_t* buffer, size_t sz);
    int read(char* result, int resultlength);
    int readCellData(int &mcc, int &mnc, long &lac, long &cellid);
    int setPIN(char *pin);
};

extern QuectelM10 gsm;

#endif

