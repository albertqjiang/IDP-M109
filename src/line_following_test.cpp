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
	while(1) {
		rlink.lf->line_following_output(rlink.request(READ_PORT_5));
		bool* lf_sensors = rlink.lf->sensor_readings;
		if (lf_sensors[0] && lf_sensors[1]) { //both front sensors read black
			rlink.mc->stop();
		}
		else if ((!lf_sensors[0]) && lf_sensors[1]) {
			rlink.mc->steer('L');
		}
		else if (lf_sensors[0] && (!lf_sensors[1])) {
			rlink.mc->steer('R');
		}
		else {
			delay(500);
			rlink.mc->forward();
		}
		
	}
	return 0;
}
