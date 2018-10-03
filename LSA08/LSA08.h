/*
  LSA08.h - Library to use Cytron LSA08.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Medha Sawhney
  Last commit done by : Medha Sawhney
*/
#ifndef LSA08_h
#define LSA08_h

// Include basic libraries
#include "Arduino.h"

class LSA08 {
  private:
  // :::::::::::::::: Private members :::::::::::::::::::
  // ================ Variables ================
  // -----------   LSA  ------------------
  int LSA_Pin_Enable;
  int LSA_Pin_Analog;
  HardwareSerial *LSASerial = NULL; //To store LSA serial
  int LSA_Val;
  char ReadMode;
  int EnableMode; //0 for active low, 1 for active HIGH
  // ------------------ Debugger ----------------------

  // ================Debugger Functions ================

  // ================LSA Functions ================
   void SetLSASerial (HardwareSerial *serial); //Storing LSA serial, to change it only once
   void ClearLSASerial(); //To clear Serial values

   public:

    // :::::::::::::::::: Public members :::::::::::::::::::::::::::
    // ================    Variables  ================
    int LSA_Flag; //0-0,1-0to35,2-35, 3-35to70,4-70,5 255
    // ===================== Constructors ===========================
    // Constructor: Empty constructor
    LSA08();
    // ===================== Member functions ========================
    //Initialization for Serial mode
    void Initialize(char mode, int Enable=0,bool ActiveLow=0,HardwareSerial *serial=&Serial1);
    //Initialization for Analog Mode
    void Initialize(char mode, int AnalogControlPin=0);
    //Read values using Analog or Serial mode
    int ReadLSA(bool DisplayControl);
    int ReadLinearFilter(bool DisplayControl);
    int ReadModeFilter(bool DisplayControl);
  };
#endif
