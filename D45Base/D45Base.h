/*
  D45Base - Library for a 4 Wheel Omni Based Holonomic Drive.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Shashank Goyal.
*/

// Check for the Flag
#ifndef D45BASE_H
#define D45BASE_H

// Include main files
#include "BotBase.h"


class D45Base : public BotBase
{
	protected:
	//############ Data Members - ##########

	// Angular Velocity for the Base.	
	int angular_vel;
	// To Reverse the Direction Pins.	
	bool *reverseDIRs;
	
	//############ Member Functions - ##########

	// Move the Base at an Angle.
	void Move_PWM_Angle(int PWM, float angle);

	public:
	
	// Set Number of Wheels.	
	D45Base();

	// Attach Pin Values to Class Variables.
	void AssignPins(int *Pwm_Pins,int *Dir_Pins,bool *ReverseDirs);

	// Set Angular Velocity.
	void SetAngularVelocity(int angular_vel);

	// Adding Rotation to Meccanum Drive.
	void Rotate(int pwm);

	// Setting Bot PWM to Zero. 
	void KillMotors();
};

#endif
