#ifndef LINE_FOLLOWER_HPP
#define LINE_FOLLOWER_HPP

#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"

class line_follower {
	robot_link* rlink;
	public:
	line_follower(robot_link* rl) {
		rlink = rl;
	}
	bool sensor_readings[4];
	void line_following_output(const int port_input); // Outputs sensor signals in a boolean array. 0th element for front left sensor and 1th element for front right sensor. 2nd element for side left sensor and 3rd element for side right sensor. TRUE for white and FALSE for black.
	

};  


#endif // LINE_FOLLOWER_HPP
