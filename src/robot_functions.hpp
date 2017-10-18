#ifndef ROBOT_FUNCTIONS
#define ROBOT_FUNCTIONS

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "mobility_control.hpp"
#include "line_follower.hpp"
//#include "led_control.hpp"
#include "arm_control.hpp"



int reversed_sign(const int& motor_speed);

class custom_robot_link:
	public robot_link
{
	int speed1;  // Calibrated forward speed for wheel 1 (positive)
	int speed2;  // Calibrated forward speed for wheel 2 (positive)
	void forward();
	public:
	line_follower lf;
	mobility_control mc;
	friend int reversed_sign(const int& motor_speed);
	void forward_with_lf(line_follower lf, int pass_cross); //This function will move the robot forward until it has passed pass_cross crosses and meets the next cross
};

#endif
