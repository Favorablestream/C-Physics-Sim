/*****************************************************************************************************************
	Filename: Bungee.cpp
	Version: 1.00
	Author: Kieran Gillibrand
	Student Number: 040-756-866
	Course Name: Numerical Computing, CST8233
	Lab Section: 300
	Assignment Name: Bungee
	Assignment Number: 3
	Due Date: Dec 2nd 2015
	Submission Date: Dec 6th 2015
	Professor's Name: Andrew Tyler
	Purpose: Provide the interface and perform calculations for a bungee jump simulation
*****************************************************************************************************************/

#include <conio.h> //_getch (), _kbhit ()
#include <iostream> //cout stream
#include <iomanip> //cout manipulators
#include <Windows.h> //Tick count functions
#include <math.h> //Math functions

#include "Bungee.h" //Bungee constants

//Function declarations
static bool almostEqual (double value1, double value2);
static void reset ();
static void endSim ();

double velocity = 0.0; //Current velocity
double height = INITIAL_HEIGHT; //Current height
double nextVelocity = 0.0; //Next velocity
double nextHeight = 0.0; //Next height
double acceleration = 0.0; //Current acceleration
double b = 0.0; //b value
double c = INITIAL_C; //c value

unsigned long long startTime = GetTickCount64 (); //Simulation start time
unsigned long long elapsedTime = 0ULL; //Simulation elapsed time (current time - elapsed)
unsigned long long deltaTime = 0ULL; //Delta time  (current time - end time)
unsigned long long endTime = startTime; //Time after calculations are finished

/*****************************************************************************************************************
	Function Name: main
	Purpose: main execution function
	Function Input Parameters: None (void)
	Function Output Parameters: An integer depending on execution
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
int main (void)
{
	char input = 0; //Character for user input

	std::cout << std::fixed << std::setprecision (3); //Set cout floating point precision (fixed, 3 decimal places)

	//User input loop
	while (input != 'q')
	{
		//Clear the screen before displaying output (or output a newline when debugging)
#ifdef DEBUG_BUNGEE
		std::cout << std::endl;
#else
		system ("CLS");
#endif

		//Display main menu
		std::cout << "Press q to exit, r to restart, w to increase drag, e to decrease drag" << std::endl;
		switch (input)
		{
			case 'w':
				std::cout << "w was pressed - increasing wind drag; wind drag: ";
			break;

			case 'e':
				std::cout << "e was pressed - reducing wind drag; wind drag: ";
			break;

			default:
				std::cout << "Starting bungee jump; wind drag: ";
			break;
		}
		std::cout << c << std::endl;

		//Get time values
		elapsedTime = GetTickCount64 () - startTime;
		deltaTime = GetTickCount64 () - endTime;

		std::cout << "Simulation Run Time: " << elapsedTime/1000ULL/60ULL << " minutes, " << (elapsedTime/1000ULL) % 60ULL << " seconds, " << elapsedTime % 1000ULL << " milliseconds" << std::endl; //Display simulation runtime

		//Calculations
		b = K * (INITIAL_HEIGHT - height); //B = k (h0 - h)
		acceleration = G - (c/M) * (velocity + A * pow (velocity/VMAX, 2.0)) - b; //dv/dt = g – (c/m)*(v + a*(v/vmax)2) – B
		nextVelocity = velocity + acceleration * ((double) (deltaTime / 1000.0)); //vi+1 = vi + accni*time_elapsed
		nextHeight = height - ((velocity + nextVelocity)/2.0) * ((double) (deltaTime / 1000.0)); //hi+1 = hi-((vi +vi+1)/2) *time_elapsed

		//Output speed and height values
		std::cout << "Speed of descent: " << nextVelocity << " m/s" << std::endl;
		std::cout << "Height above ground: " << nextHeight << " m" << std::endl;

#ifdef DEBUG_BUNGEE
		std::cout << "DEBUG_BUNGEE: Velocity: " << velocity << ", Height: " << height << ", nextVelocity: " << nextVelocity << ", nextHeight: " << nextHeight << ", acceleration: " << acceleration << ", b: " << b << ", c: " << c << ", elapsedTime (s): " << (double) (elapsedTime / 1000.0) << std::endl;
#endif

		//The next values will become the current for the next loop iteration
		velocity = nextVelocity;
		height = nextHeight;

		endTime = GetTickCount64 (); //Set the endtime

		//Sleep when not debugging to stop flickering and increase readability, time will continue to be counted
#ifndef DEBUG_BUNGEE
		Sleep (DELAY);
#endif

		//If a key is pressed then perform an action
		if (_kbhit ())
		{
			input = (char) _getch (); //Get the key as input

			switch (input)
			{
				//Exit
				case 'q':
					exit (EXIT_SUCCESS);

				//Increase c
				case 'w':
					if (c < MAX_C)
						++c;
				break;

				//Decrease c
				case 'e':
					if (c > MIN_C)
						--c;
				break;

				//Reset
				case 'r':
					reset ();
				break;
			}
		}

		//Unsafe landing (velocity > 1.0 m/s)
		if (nextVelocity > MAX_SAFE_VELOCITY && nextHeight < LANDING_HEIGHT)
		{
			std::cout << std::endl << "You died =(: Press q to exit, r to restart" << std::endl;
			endSim ();
		}

		//Safe landing (velocity < 1.0 m/s)
		else if (nextVelocity < MAX_SAFE_VELOCITY && nextHeight < LANDING_HEIGHT)
		{
			std::cout << std::endl << "You landed =): Press q to exit, r to restart" << std::endl;
			endSim ();
		}

		//Stuck in the air (acceleration ~= 0 and b ~= g)
		else if (almostEqual (acceleration, 0.0) && almostEqual (b, G))
		{
			std::cout << std::endl << "You are stuck in the air =(: Press q to exit, r to restart" << std::endl;
			endSim ();
		}
	}
}

/*****************************************************************************************************************
	Function Name: almostEqual ()
	Purpose: Check if two doubles are close to equal (may never be exactly equal due to inaccuracy)
	Function Input Parameters: double value1: The first double value, double value2: The second double value
	Function Output Parameters: A boolean (true if the values are almost equal, false otherwise)
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
static bool almostEqual (double value1, double value2)
{
	return abs (value1 - value2) < PRECISION;
}

/*****************************************************************************************************************
	Function Name: reset ()
	Purpose: Reset the simulation's values to start again
	Function Input Parameters: None (void)
	Function Output Parameters: None (void)
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
static void reset (void)
{
	//Reset equation values
	velocity = 0.0;
	height = INITIAL_HEIGHT;
	nextVelocity = 0.0;
	nextHeight = INITIAL_HEIGHT;
	acceleration = 0.0;
	b = 0.0;
	c = INITIAL_C;

	//Reset timing
	startTime = GetTickCount64 ();
	elapsedTime = 0ULL;
	deltaTime = 0ULL;
	endTime = startTime;
}

/*****************************************************************************************************************
	Function Name: endSim ()
	Purpose: Allow the user to exit or reset when the simulation is ended for them (death, landing, or stuck)
	Function Input Parameters: None (void)
	Function Output Parameters: None (void)
	Version: 1.00
	Author: Kieran Gillibrand
*****************************************************************************************************************/
static void endSim (void)
{
	char input = 0; //Character for user input

	input = (char) _getch (); //Get the character

	switch (input)
	{
		//Exit
		case 'q':
			exit (EXIT_SUCCESS);

		//Reset
		case 'r':
			reset ();
		break;
	}
}