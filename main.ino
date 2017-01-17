#include <I2Cdev.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include "Wire.h"
SoftwareSerial Serialdevice(8,9);//Rx Tx

#define i2cdevisavailable 2
#define serdevisavailable 3
#define spidevisavailable 4  

int row[]={0,224,128,96,64,192,160,32};
int col[]={0,2,4,12,8,10,6,14};

#define S20 7
#define S21 6
#define S22 5
#define S10 A3
#define S11 A2
#define S12 A1


int time=500;
byte i2cvalue=B00000000;
byte spivalue=B00000000;
int i=0;
void tick()
{
  //Code to display tick on LED matrix
  int temp1=PORTD;
  int temp2=PORTC;
  for(int i=0;i<500;i++)
  {
   PORTD=row[3];
  PORTC=col[0];
  delayMicroseconds(100);
  PORTD=row[4];
  PORTC=col[1];
  delayMicroseconds(100);
  PORTD=row[5];
  PORTC=col[2];
  delayMicroseconds(100);
  PORTD=row[4];
  PORTC=col[3];
  delayMicroseconds(100);
  PORTD=row[3];
  PORTC=col[4];
  delayMicroseconds(100);
  PORTD=row[2];
  PORTC=col[5];
  delayMicroseconds(100);
  PORTD=row[1];
  PORTC=col[6];
  delayMicroseconds(100);
  PORTD=row[0];
  PORTC=col[7];
  delayMicroseconds(100); 
 }
 PORTD=temp1;
 PORTC=temp2;
 
}
void cross()
{
  //Code to display cross on LED matrix
  int temp1=PORTD;
  int temp2=PORTC;
  
  for(int i=0;i<500;i++)
  {
  PORTD=row[0];
  PORTC=col[0];
  delayMicroseconds(100);
  PORTD=row[1];
  PORTC=col[1];
  delayMicroseconds(100);
  PORTD=row[2];
  PORTC=col[2];
  delayMicroseconds(100);
  PORTD=row[3];
  PORTC=col[3];
  delayMicroseconds(100);
  PORTD=row[4];
  PORTC=col[4];
  delayMicroseconds(100);
  PORTD=row[5];
  PORTC=col[5];
  delayMicroseconds(100);
  PORTD=row[6];
  PORTC=col[6];
  delayMicroseconds(100);
  PORTD=row[7];
  PORTC=col[7];
  delayMicroseconds(100);
  PORTD=row[7];
  PORTC=col[0];
  delayMicroseconds(100);
  PORTD=row[6];
  PORTC=col[1];
  delayMicroseconds(100);
  PORTD=row[5];
  PORTC=col[2];
  delayMicroseconds(100);
  PORTD=row[4];
  PORTC=col[3];
  delayMicroseconds(100);
  PORTD=row[3];
  PORTC=col[4];
  delayMicroseconds(100);
  PORTD=row[2];
  PORTC=col[5];
  delayMicroseconds(100);
  PORTD=row[1];
  PORTC=col[6];
  delayMicroseconds(100);
  PORTD=row[0];
  PORTC=col[7];
  delayMicroseconds(100);  
 }
 PORTD=temp1;
 PORTC=temp2;
 pinMode(i2cdevisavailable,INPUT);
 
}

void setup()
{
  
  // initialize SPI:
  SPI.begin(); 
  //Initialize I2C communication
  Wire.begin();
  
  Serial.begin(9600);
 
  pinMode(serdevisavailable,INPUT);
  pinMode(i2cdevisavailable,INPUT);
  pinMode(spidevisavailable,INPUT);
  pinMode(S10,OUTPUT);
  pinMode(S11,OUTPUT);
  pinMode(S12,OUTPUT);
  pinMode(S20,OUTPUT);
  pinMode(S21,OUTPUT);
  pinMode(S22,OUTPUT);
  

}
  void loop()
  {
 
    //check for Serial device availability 
  if(digitalRead(serdevisavailable))
  { 
     Serialdevice.begin(9600);
     //Serialdevice.write("AT");
     //delay(500);
     if(Serialdevice.available())
       {
         Serial.println("Serial device is functioning properly");
         tick(); 
       }
     else
       {
         Serial.println("Serial Device is not working properly");
         cross();
       }
  }
  else
  {
     Serial.println("No Serial device connected");
  }
   
    
    //Check for I2C device availability and functionality
    if(digitalRead(i2cdevisavailable))
    {
      for(i=0;i<127;i++)
      {
        //Wire.beginTransmission(i);
        //Wire.write("vc");
        //if(Wire.available())
        //i2cvalue=Wire.endTransmission(i);
        
        i2cvalue=Wire.requestFrom(i,8,true);
        //scans all slave address and requests one byte value
        if(i2cvalue!=0)
        break;//If something is returned, there is a device available for data transfer...i.e the device is not bricked
      }
      if(i2cvalue!=0)
      {
        Serial.println("I2C Device is Functioning properly");
        tick();
      }
      else
      {
        Serial.println("I2C device not functioning properly");
        cross();
      }
    }
     
     else
    {
    Serial.println("No I2C device connected");
    }
    
     
    //Check for SPI device availaility
    if(digitalRead(spidevisavailable))
    {
    for(i=0;i<255;i++)
      {
        spivalue=SPI.transfer(i);
        if(spivalue!=0)
        break;
      }
      if(spivalue!=0)
      {
        Serial.println("SPI device is working properly");
        tick();
      }
      else
      {
        Serial.println("SPI device is not working properly");
        cross();
      }
    }
    else
    { 
      Serial.println("SPI device not connected");
    } 
    
  }
