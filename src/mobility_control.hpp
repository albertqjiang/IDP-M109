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
		void forward(robot_link* rlink); // move forward
		void stop(robot_link* rlink);
		void turn(const int turning_code); // turn left if turning_code is -1, right if it is 1
		void forward_with_lf(robot_link* rlink, line_follower lf, int cross_to_pass);
			//This function will move the robot forward until it has passed pass_cross crosses and meets the next cross
		void move_till_cross(robot_link* rlink, line_follower lf);
		void move_across_cross(robot_link* rlink, line_follower lf);
};  


#endif // MOBILITY_CONTROL_HPP
