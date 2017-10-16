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

	 while (1) {// Main loop
		// Collectiion process
		forward_with_lf(lf, 1);
		collect();
		detect();
		for (int i = 0; i < 5; i++) {
			forward_with_lf(lf, 0);
			collect();
			detect();
		}

		// delivering process
		
	} 
	/* while (1) {
		cout<<"sensors read input"<<endl;
		cout<<rlink.request(READ_PORT_0)<<endl;
		cout<<rlink.request(READ_PORT_1)<<endl;
		cout<<rlink.request(READ_PORT_2)<<endl;
		cout<<rlink.request(READ_PORT_3)<<endl;
		cout<<rlink.request(READ_PORT_4)<<endl;
		cout<<rlink.request(READ_PORT_5)<<endl;
		cout<<rlink.request(READ_PORT_6)<<endl;
		cout<<rlink.request(READ_PORT_7)<<endl;	
		delay(1000);



	} */
	
	return 0;
}
