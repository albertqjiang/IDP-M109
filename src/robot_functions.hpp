#ifndef ROBOT_FUNCTIONS
#define ROBOT_FUNCTIONS

#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
using namespace std;

int reversed_sign(const int& motor_speed);

class custom_robot_link:
	public robot_link
{
	int speed1;  // Calibrated forward speed for wheel 1 (positive)
	int speed2;  // Calibrated forward speed for wheel 2 (positive)
	public:
	void forward();
	friend int reversed_sign(const int& motor_speed);
};

#endif
