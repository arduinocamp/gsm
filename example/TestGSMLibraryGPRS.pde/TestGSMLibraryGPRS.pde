#include "QuectelM10.h"
#include <NewSoftSerial.h>
#include "inetGSM.h"
/*#include "LOG.h"

#define __LOG_LEVEL 5
LOG logme(__LOG_LEVEL);
*/
/*
 * We should put here some copyright stuff.
 *
 * This program is developed just to test-develop the Arduino-TID-GSM libraries.
*/

InetGSM inet;
char msg[200];
int numdata;

void setup() 
{
  //Serial connection.
  Serial.begin(9600);
  Serial.println("GSM Shield testing.");
  //Start configuration.
  if (gsm.begin())
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");

  //GPRS attach
  if (gsm.attachGPRS("movistar.es", "movistar", "movistar"))
    Serial.println("status=ATTACHED");
  else Serial.println("status=ERROR");
  //TCP Client GET.
  numdata=inet.httpGET("www.google.com", 80, "/", msg, 200);
  Serial.println("\nNumber of data received:");
  Serial.println(numdata);  
  Serial.println("Data received:"); 
  Serial.println(msg); 

  //Tweet
  inet.tweet("*********************key************", "An Arduino at #cpes15");
  
  // TCP Server.
  if (gsm.connectTCPServer(80))
    Serial.println("status=TCPSERVERWAIT");
  else Serial.println("ERROR in Server");
};

void loop() 
{
  if (gsm.connectedClient())
  {
    gsm.read(msg, 200);
    Serial.println(msg);
    gsm.write((const uint8_t*)"Read Data", 9);
  }
};

