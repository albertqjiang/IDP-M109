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
	robot_link* rlink;
	line_follower* lf;

	public:
		void initialize(robot_link* rl, line_follower* line_f) {
			rlink = rl;
			lf = line_f
		}
		void forward(); // move forward
		void stop(;
		void turn(const int turning_code); // turn left if turning_code is -1, right if it is 1
		void forward_with_lf(int cross_to_pass);
			//This function will move the robot forward until it has passed pass_cross crosses and meets the next cross
		void move_till_cross();
		void move_across_cross();
};  


#endif // MOBILITY_CONTROL_HPP
