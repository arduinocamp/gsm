#include <QuectelM10.h>
#include <NewSoftSerial.h>

/*
 * We should put here some copyright stuff.
 *
 * This program is developed just to test-develop the Arduino-TID-GSM libraries.
*/

char msg[200];
int numdata;

void setup() 
{
  int res;
  //Serial connection.
  Serial.begin(9600);
  Serial.println("GSM Shield testing.");
  //Start configuration.
  if (gsm.begin("6104"))
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
  
  if (gsm.sendSMS("xxxxx", "Arduino SMS Prueba 1"))
    Serial.println("\nSMS sent OK");

};

void loop() 
{
  char smsbuffer[160];
  char n[20];

  if(gsm.readSMS(smsbuffer, 160, n, 20))
  {
    Serial.println(n);
    Serial.println(smsbuffer);
  }
  delay(1000);
};


