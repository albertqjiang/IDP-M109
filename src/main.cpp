#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"

#define ROBOT_NUM  7                         // The id number (see below)
// robot_link  rlink;                            // datatype for the robot link
custom_robot_link  rlink;  // Our customized robot_link class
double PARAMETER_TO_CALIBRATE = 1.0;

int main () {
	int   val;                                // data from microprocessor
	if (!rlink.initialise (ROBOT_NUM)) {      // setup the link
		cout << "Cannot initialise link" << endl;
		rlink.print_errs("    ");
	}
	val = rlink.request (TEST_INSTRUCTION);   // send test instruction
	if (val == TEST_INSTRUCTION_RESULT) {     // check result
		cout << "Test passed" << endl;
                            // all OK, finish
	}
	else if (val == REQUEST_ERROR) {
		cout << "Fatal errors on link:" << endl;
		rlink.print_errs();
	}
	else {
		cout << "Test failed (bad value returned)" << endl;
                exit(1);     // error, finish
	}

	// Collectiion process
	int golf_balls[6] = {0};
	rlink.mc.forward_with_lf(lf, 1);
	rlink.ac.collect();
	golf_balls[0] = rlink.det.classify();
	if (golf_balls[0] == -1) {
		rlink.ac.collect();
		golf_balls[0] = rlink.det.classify();		

	}//collecting first ball
	for (int i = 0; i < 5; i++) {
		rlink.mc.forward_with_lf(lf, 0);
		rlink.ac.collect();
		golf_balls[1] = rlink.det.detect();
		if (golf_balls[i] == -1) {
			rlink.ac.collect();
			golf_balls[i] = rlink.det.classify();		
		}
	}//collecting ball 2-6

	// delivering process
	rlink.mc.turn(-1); //turn left
	rlink.mc.forward_with_lf(lf, 0); //go to 1st delivery point
	int ball_no_deliver = find_ball_no(golf_balls, 1); // 1 here indicates the first delivery point
	while (ball_no_deliver != -1) {
		rlink.ac.deliver(ball_no_deliver);
		ball_no_deliver = find_ball_no(golf_balls, 1);
	}
	
	rlink.mc.forward_with_lf(lf, 1);
	ball_no_deliver = find_ball_no(golf_balls, 2); //2 here indicates the second delivery point
	while (ball_no_deliver != -1) {
		rlink.ac.deliver(ball_no_deliver);
		ball_no_deliver = find_ball_no(golf_balls, 2);
	}

	rlink.mc.turn(-1); // turn left
	rlink.mc.forward_with_lf(lf, 2);
	rlink.mc.turn(-1); // turn left
	rlink.mc.forward(PARAMETER_TO_CALIBRATE);
	rlink.mc.turn(-1); // turn left


	ball_no_deliver = find_ball_no(golf_balls, 3); //3 here indicates the third delivery point
	while (ball_no_deliver != -1) {
		rlink.ac.deliver(ball_no_deliver);
		ball_no_deliver = find_ball_no(golf_balls, 3);
	}

	rlink.mc.forward(PARAMETER_TO_CALIBRATE);
	ball_no_deliver = find_ball_no(golf_balls, 4); //4 here indicates the fourth delivery point
	while (ball_no_deliver != -1) {
		rlink.ac.deliver(ball_no_deliver);
		ball_no_deliver = find_ball_no(golf_balls, 4);
	}

	rlink.mc.forward(PARAMETER_TO_CALIBRATE);
	ball_no_deliver = find_ball_no(golf_balls, 5); //5 here indicates the fifth delivery point
	while (ball_no_deliver != -1) {
		rlink.ac.deliver(ball_no_deliver);
		ball_no_deliver = find_ball_no(golf_balls, 5);
	}

	
	return 0;
}
