#ifndef MOBILITY_CONTROL_HPP
#define MOBILITY_CONTROL_HPP

#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "line_follower.hpp"

class mobility_control {
	public:
		void forward(const double time); // move forward for a certain period of time
		void stop();
		void turn(const int turning_code); // turn left if turning_code is -1, right if it is 1
		void forward_with_lf(line_follower lf, int cross_to_pass);
};  


#endif // MOBILITY_CONTROL_HPP
