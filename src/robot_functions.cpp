#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"
using namespace std;

int reversed_sign(const int& motor_speed) {
	// cout << motor_speed << " " << (0b10000000 ^ motor_speed) << endl;
	return 0b10000000 ^ motor_speed;
}

void custom_robot_link::forward() {
	command(MOTOR_2_GO, speed2);
	command(MOTOR_1_GO, reversed_sign(speed1));
}

