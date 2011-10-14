#ifndef GSM_H
#define GSM_H

#include <NewSoftSerial.h>
#include <inttypes.h>
#include "WideTextFinder.h"

#define ctrlz 26 //Ascii character for ctr+z. End of a SMS.
#define cr    13 //Ascii character for carriage return. 
#define lf    10 //Ascii character for line feed. 

class GSM
{
  public:
    enum GSM_st_e { ERROR, IDLE, READY, ATTACHED, TCPSERVERWAIT, TCPCONNECTEDSERVER, TCPCONNECTEDCLIENT };

  private:
    int _status;
    
  protected:
    NewSoftSerial _cell;
    WideTextFinder _tf;
    inline void setStatus(GSM_st_e status) { _status = status; }
    virtual int setPIN(char *pin);
    int isIP(const char* cadena);

  public:
    GSM();
    inline int getStatus(){   return _status; };
    int begin(char* pin=0);
    virtual int restart(char* pin=0);
    virtual int start(char* pin=0);
    virtual int shutdown();
    virtual int getCCI(char* cci);
    virtual int getIMEI(char* imei);

    virtual int sendSMS(const char* to, const char* msg);
    virtual boolean availableSMS();
    virtual boolean readSMS(char* msg, int msglength, char* number, int nlength);
    virtual boolean readCall(char* number, int nlength);
    virtual boolean call(char* number, unsigned int milliseconds);
    virtual int attachGPRS(char* domain, char* dom1, char* dom2);
    virtual int dettachGPRS();
    virtual int connectTCP(const char* server, int port);
    virtual int disconnectTCP();
    virtual int connectTCPServer(int port);
    virtual boolean connectedClient();
    virtual int readCellData(int &mcc, int &mnc, long &lac, long &cellid);
    virtual int write(uint8_t c);
    virtual int write(const char* str);
    virtual int write(const uint8_t* buffer, size_t sz);
    virtual int read(char* result, int resultlength);
	virtual uint8_t read();
    

};

#endif
