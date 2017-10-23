#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"
#include "mobility_control.hpp"

using namespace std;

int speed = 127;

void mobility_control::forward(custom_robot_link* rlink) {
	
	rlink.command(MOTOR_1_GO, speed);
	rlink.command(MOTOR_2_GO, speed);
}

void mobility_control::stop(custom_robot_link* rlink) {
	rlink.command(MOTOR_1_GO, 0);
	rlink.command(MOTOR_2_GO, 0);
}

void mobility_control::forward_with_lf(custom_robot_link* rlink, line_follower lf, int cross_to_pass) {
	

}

void move_till_cross(custom_robot_link* rlink, line_follower lf) {
	lf.line_following_output(rlink.request(READ_INPUT_7));
	while (!(lf.sensor_readings[0] && lf.sensor_readings[1])) {
		// Unless both front sensors detect white, repeat doing this
		if ((!lf.sensor_readings[0]) && (!lf.sensor_readings[1])) {
			// Both front sensors are black
			rlink.command(BOTH_MOTORS_GO_SAME, speed);
		}

		else if ((!lf.sensor_readings[0]) && (lf.sensor_readings[1])) {
			// Left motor is black and right motor is white
			// Turn right
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, speed);
		}

		else if ((lf.sensor_readings[0]) && (!lf.sensor_readings[1])) {
			// Left motor is white and right motor is black
			// Turn left
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, speed + 128);
		}
		lf.line_following_output(rlink.request(READ_INPUT_7));
	}
}

void move_across_cross(custom_robot_link* rlink, line_follower lf) {
	lf.line_following_output(rlink.request(READ_INPUT_7));
	while (lf.sensor_readings[0] || lf.sensor_readings[1]) {
		if ((!lf.sensor_readings[0]) && (lf.sensor_readings[1])) {
			// Left motor is black and right motor is white
			// Turn left
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, speed);
		}

		else if ((lf.sensor_readings[0]) && (!lf.sensor_readings[1])) {
			// Left motor is white and right motor is black
			// Turn right
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, speed + 128);
		}
		lf.line_following_output(rlink.request(READ_INPUT_7));
	}
}