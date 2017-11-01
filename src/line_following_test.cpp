#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"

#define ROBOT_NUM 7       // The id number (see below)
// robot_link rlink;         // datatype for the robot link
custom_robot_link rlink;  // Our customized robot_link class
double PARAMETER_TO_CALIBRATE = 1.0;

int main() {
	// Actuator testing
	while (1) {
		rlink.ac->extend();
		delay(2000);
		rlink.ac->extend();
		cout << "Stop\n";
	}
	return 0;
	
	// Arm motor testing
	int ss = 80;
	while (1) {
		rlink.rlink.command(MOTOR_3_GO, ss);
		delay(500);
		rlink.rlink.command(MOTOR_3_GO, 0);
		ss = reversed_sign(ss);
		cout << "Stop\n";
	}
	return 0;

	// Line following and turning testing
	while(1) {
		//rlink.mc->turn('l'); break;
		rlink.lf->line_following_output(rlink.request(READ_PORT_5));
		bool* lf_sensors = rlink.lf->sensor_readings;
		if ((!lf_sensors[0]) && (!lf_sensors[1])) { //both front sensors read black
			rlink.mc->forward();
			cout << "F" << endl;
		}
		else if ((!lf_sensors[0]) && lf_sensors[1]) {
			rlink.mc->steer('R');
			cout << "R" << endl;
		}
		else if (lf_sensors[0] && (!lf_sensors[1])) {
			rlink.mc->steer('L');
			cout << "L" << endl;
		}
		else {
			cout << "STOP" << endl;
			rlink.mc->stop();
			break;
		}
		
	}
	rlink.mc->turn('R');
	while(1) {
		//rlink.mc->turn('l'); break;
		rlink.lf->line_following_output(rlink.request(READ_PORT_5));
		bool* lf_sensors = rlink.lf->sensor_readings;
		if ((!lf_sensors[0]) && (!lf_sensors[1])) { //both front sensors read black
			rlink.mc->forward();
			cout << "F" << endl;
		}
		else if ((!lf_sensors[0]) && lf_sensors[1]) {
			rlink.mc->steer('R');
			cout << "R" << endl;
		}
		else if (lf_sensors[0] && (!lf_sensors[1])) {
			rlink.mc->steer('L');
			cout << "L" << endl;
		}
		else {
			cout << "STOP" << endl;
			rlink.mc->stop();
			break;
		}
		
	}

	return 0;
}

