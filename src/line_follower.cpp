#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "line_follower.hpp"

using namespace std;

void line_follower::line_following_output(const int port_input) {
	sensor_readings[0] = (0b0001 & port_input);
	sensor_readings[1] = (0b0010 & port_input);
	sensor_readings[2] = (0b0100 & port_input);
	sensor_readings[3] = (0b1000 & port_input);
	
}
