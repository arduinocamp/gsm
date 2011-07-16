#include "GSM.h"
#include "WideTextFinder.h"

#define _GSM_TXPIN_ 2
#define _GSM_RXPIN_ 3

GSM::GSM():_cell(_GSM_TXPIN_,_GSM_RXPIN_),_tf(_cell, 10),_status(IDLE)
{
  
};


int GSM::begin()
{
  _cell.begin(9600);
  setStatus(IDLE);
  return start();
}

int GSM::restart(){ return 1;}

int GSM::write(uint8_t c)
{
  if ((_status == TCPCONNECTEDCLIENT) ||(_status == TCPCONNECTEDSERVER) )
    return write(&c, 1);
  else
    return 0;
}

int GSM::write(const char* str)
{
  if ((_status == TCPCONNECTEDCLIENT) ||(_status == TCPCONNECTEDSERVER) )
      return write((const uint8_t*)str, strlen(str));
  else
      return 0;
}

int GSM::start(){return 0;};
int GSM::shutdown(){return 0;};
int GSM::sendSMS(const char* to, const char* msg){return 0;};
int GSM::attachGPRS(char* domain, char* dom1, char* dom2){return 0;};
int GSM::dettachGPRS(){return 0;};
int GSM::connectTCP(const char* server, int port){return 0;};
int GSM::disconnectTCP(){return 0;};
int GSM::connectTCPServer(int port){return 0;};
boolean GSM::connectedClient(){return false;};
int GSM::readCellData(int &mcc, int &mnc, long &lac, long &cellid){return 0;};
int GSM::write(const uint8_t* buffer, size_t sz){return 0;};
int GSM::read(char* result, int resultlength){return 0;};
boolean GSM::availableSMS(){return false;};
boolean GSM::readSMS(char* msg, int msglength, char* number, int nlength){return false;};
boolean GSM::readCall(char* number, int nlength){return false;};
boolean GSM::call(char* number, unsigned int milliseconds){return false;};






