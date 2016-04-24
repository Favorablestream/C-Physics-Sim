/*****************************************************************************************************************
	Filename: Bungee.h
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
	Purpose: Define constants for the bungee calculations
*****************************************************************************************************************/

#ifndef BUNGEE_H
#define BUNGEE_H

//#define DEBUG_BUNGEE

const double INITIAL_HEIGHT = 400.0; //Starting height
const double INITIAL_C = 10.0; //Starting c
const double MAX_C = 10.0; //Maximum c
const double MIN_C = 1.0; //Minimum c

const double K = 0.04; //K constant for bungee cord
const double G = 9.8; //Acceleration due to gravity constant
const double M = 68.0; //M constant
const double A = 8.0; //A constant
const double VMAX = 46.0; //VMAX constant

const double LANDING_HEIGHT = 1.0; //Height considered a landing (less then this height)
const double MAX_SAFE_VELOCITY = 1.0; //Maximum velocity considered safe when landing

const unsigned long DELAY = 60UL; //Delay for user interface (to stop flickering and increase readability)

const double PRECISION = 1e-5; //Precision value for almost equal funcion

#endif