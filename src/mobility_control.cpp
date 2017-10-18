#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "mobility_control.hpp"

using namespace std;

void forward() {
	int speed = 127;
	rlink.command(MOTOR_1_GO, speed);
	rlink.command(MOTOR_2_GO, speed);
}

void stop() {
	rlink.command(MOTOR_1_GO, 0);
	rlink.command(MOTOR_2_GO, 0);
}
