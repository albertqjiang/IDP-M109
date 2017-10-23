#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "mobility_control.hpp"

using namespace std;

void mobility_control::forward() {
	int speed = 127;
	rlink.command(MOTOR_1_GO, speed);
	rlink.command(MOTOR_2_GO, speed);
}

void mobility_control::stop() {
	rlink.command(MOTOR_1_GO, 0);
	rlink.command(MOTOR_2_GO, 0);
}

void mobility_control::forward_with_lf(line_follower lf, int cross_to_pass) {
	
}