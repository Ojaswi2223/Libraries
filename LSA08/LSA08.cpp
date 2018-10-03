/*
BotBase.cpp - Library to deal with all kinds of bot bases RM deals with
Copyright (c) 2018 RoboManipal. All right reserved
File created by : Medha Sawhney
Last commit done by : Medha Sawhney
*/
#include "LSA08.h"

// ===================== Constructor ===========================
LSA08::LSA08()
{

}
// ===================== Member functions ========================

void LSA08::SetLSASerial(HardwareSerial  *serial)
{ //Initializing LSA serial
  LSASerial = serial;
}

void LSA08::Initialize(char mode, int Enable,bool ActiveLow,HardwareSerial *serial)
{
  ReadMode=mode;
  if(ReadMode=='s')
  {
    //To initialize LSA Serial
    SetLSASerial(serial);
    //Enable mode - active low (0)or active high (1)
    if(ActiveLow==0)
    EnableMode=0;
    else
    EnableMode=1;
    //Enable Pin for LSA
    LSA_Pin_Enable=Enable;
  }
}

void LSA08::Initialize(char mode, int AnalogControlPin)
{
  //Reading mode - Analog
  ReadMode=mode;
  if(ReadMode=='a')
  {//Analog Pin for LSA analog input
    LSA_Pin_Analog=AnalogControlPin;
  }
}

void LSA08::ClearLSASerial()
{ //To clear LSA serial
  if(ReadMode=='s')
  {
    while (LSASerial->available())
    {
      LSASerial->read();
    }
  }
}

int LSA08::ReadLSA(bool print)
{
//Reading LSA values using Serial
  if( ReadMode=='s')
  {
    //Clear Serial before reading
    ClearLSASerial();
    if(EnableMode==0)
    //Active low enable
    digitalWrite(LSA_Pin_Enable,LOW);
    else
    //Active high enable
    digitalWrite(LSA_Pin_Enable, HIGH);
    delayMicroseconds(1000);
    while (!(LSASerial->available()));
    while (LSASerial->available())
    {//Reading from serial
      LSA_Val = LSASerial->read();
      //To check for noise while reading
      if(LSA_Val==255)
      continue;
      else
      break;
    }
//disabling enable pin after reading from LSA
    if(EnableMode==0)
    digitalWrite(LSA_Pin_Enable,HIGH);
    else
    digitalWrite(LSA_Pin_Enable, LOW);
    ClearLSASerial();
  }
//Reading Analog LSA values
  if(ReadMode=='a')
  {
    LSA_Val = analogRead(LSA_Pin_Analog);
    if (LSA_Val <= 920)
    {//Mapping raw analog values to 0-70
      LSA_Val = map(LSA_Val, 0, 920, 0, 70);
    }
    else
    LSA_Val = 255;
  }

// values to determine in which region the line is with respect to LSA
  if(LSA_Val==0)
  //leftmost of LSA
  LSA_Flag=0;
  if(LSA_Val>0&&LSA_Val<35)
  //between 0 to 35
  LSA_Flag=1;
  if(LSA_Val==35)
  //at center-35
  LSA_Flag=2;
  if(LSA_Val>35&&LSA_Val<70)
  //between 35 to 70
  LSA_Flag=3;
  if(LSA_Val==70)
  //rightmost of LSA
  LSA_Flag=4;
  if(LSA_Val>255)
  //LSA is not in the line
  LSA_Flag=5;

  if(print==1)
  Serial.println(LSA_Val);

  return LSA_Val;

}
