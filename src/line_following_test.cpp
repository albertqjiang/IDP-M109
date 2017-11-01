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
	// TODO: The rotation motor can't be calibrated due to crazy resistance forces of the wires.
	// TODO: need softer wires and better wire arrangement
	// Actuator testing
	while (1) {
		int to_slot_0 = 1250;
		rlink.ac->extend();
		delay(2000);
		rlink.ac->grab();
		delay(2000);
		rlink.ac->contract();
		delay(2000);
		rlink.ac->right(to_slot_0); // Turn right for to_slot_0 ms.
		delay(2000);
		rlink.ac->extend();
		delay(2000);
		rlink.ac->release();
		delay(2000);
		rlink.ac->contract();
		delay(2000);
		rlink.ac->left(to_slot_0); // Turn left for to_slot_0 ms.
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

