#include "D45Base.h"

// Set Number of Wheels to Four.
D45Base :: D45Base()	
{
	this->setNumberOfWheelsTo(4);
}

// Assign Pin Values to the Class Variables -
void D45Base :: AssignPins(int *PWM_PINs, int *DIR_PINs, bool *reversePINs) 
{
	// Call the function of super class and assign PWM, DIR pins
	this->AddMotorDriverPins(PWM_PINs, DIR_PINs);

	// Assign reverse directions
	this->reverseDIRs = reversePINs;

	// Set Angular Velocity to 0 by Default.
	this->angular_vel = 0;
	
	// Debugger output
	String message = "Wheel Reverse DIRs : ";
	for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) 
	{
		message.concat(reversePINs[i]);
		message.concat(" ");
	}
	this->DebuggerOutput(2, message);
}

// Set Angular Velocity.
void D45Base :: SetAngularVelocity(int angular_vel)
{
	this->angular_vel = angular_vel;
}	

// Move Base at an Angle -
void D45Base :: Move_PWM_Angle(int PWM, float angle) 
{
	/*#################### Vector Equations #########################

	[ V1 ]		[ 0	  1  1]		[ -0.707 * V * cos(angle) + 0.707 * V * sin(angle) + angular_vel]
	[ V2 ]	=	[-1	  0  1]	 *	[ -0.707 * V * cos(angle) + 0.707 * V * sin(angle) + angular_vel]	
	[ V3 ]		[ 0	 -1  1]		[	  						angular_vel 						]
	[ V4 ]		[ 1	  0  1]		

	// Refer to README for Derivation.

	###############################################################*/
	
	// PWM vector created from directions.
	int PWM_vector[4] = 
	{
		(int)((-0.707 * PWM * cos(angle)) + (0.707 * PWM * sin(angle)) + angular_vel), 
		(int)((-0.707 * PWM * cos(angle)) - (0.707 * PWM * sin(angle)) + angular_vel), 
		(int)((0.707 * PWM * cos(angle)) - (0.707 * PWM * sin(angle)) + angular_vel),
		(int)((0.707 * PWM * cos(angle)) + (0.707 * PWM * sin(angle)) + angular_vel)
	};

	// Dir Vectors for Dir Pins.
	int DIR_vector[4] = {LOW, LOW, LOW, LOW};
	// PWM Magnitude Vector.
	int PWM_abs_vector[4];

	// Get the DIR_values vector from PWM_vector and get PWM_values
	for (int i = 0; i < NUMBER_OF_WHEELS; i++)
	{
		// Set Direction Vectors according to Positive or Negative PWM.
		DIR_vector[i] = ((PWM_vector[i] >= 0) ? HIGH : LOW);
		if (this->reverseDIRs[i] == true) 
		{
			// In the Case the Motor Pins are Reversed on the Motor Driver.
			DIR_vector[i] = !DIR_vector[i];
		}
		PWM_abs_vector[i] = fabs(PWM_vector[i]);
	}
	// Assigning the Magnitude of the Wheels.
	this->PWM_values = PWM_abs_vector;
	// Assigning the Direction of the Wheels.
	this->DIR_values = DIR_vector;

	// Debugger Monitor -
	String message = "";
	for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) 
	{
		message.concat(PWM_vector[i]);
		message.concat(":");
		message.concat(this->PWM_values[i]);
		message.concat(":");
		message.concat(this->DIR_values[i]);
		message.concat(" ");
	}
	message.concat("\n");
	this->DebuggerOutput(2, message);

	// Attach Motion to the Wheels.
	for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) 
	{
		this->MoveMotor(i);
	}
}

// Rotate AntiClockwise for Poisitive PWM and Rotate Clockwise for Negative PWM -
void D45Base :: Rotate(int pwm)
{	 
	// Set the Angular Velocity -
	SetAngularVelocity(pwm);

	// Move th Base - 
	this->Move_PWM_Angle(0,0);
}

// Setting the Bot at Rest.
void D45Base :: KillMotors()
{	
	// Set the Angular Velocity to Zero.
	SetAngularVelocity(0);

	// Set Base Pwm and angle as Zero. 
	this->Move_PWM_Angle(0,0);
}		
