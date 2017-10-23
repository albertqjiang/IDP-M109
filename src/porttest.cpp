#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>

#define ROBOT_NUM  7                         // The id number (see below)
// robot_link  rlink;                            // datatype for the robot link
robot_link  rlink;  // Our customized robot_link class

int main() {
    
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
    while (1) {
        delay(100);
        cout << "0 " << rlink.request(READ_PORT_0) << endl;
        cout << rlink.request(READ_PORT_1) << endl;
        cout << rlink.request(READ_PORT_2) << endl;
        cout << rlink.request(READ_PORT_3) << endl;
        cout << rlink.request(READ_PORT_4) << endl;
        cout << rlink.request(READ_PORT_5) << endl;
        cout << rlink.request(READ_PORT_6) << endl;
        cout << rlink.request(READ_PORT_7) << endl;
    }
}
