#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>

#define ROBOT_NUM  7                         // The id number (see below)
// robot_link  rlink;                            // datatype for the robot link
custom_robot_link  rlink;  // Our customized robot_link class

int main() {
    
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
