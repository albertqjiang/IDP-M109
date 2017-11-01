#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "arm_control.hpp"
#include "robot_functions.hpp"

arm_control::arm_control(robot_link* rl) {
        rlink = rl;
}

void arm_control::collect() {

}

void arm_control::extend() {
    rlink->command(WRITE_PORT_0, 127);
	rlink->command(WRITE_PORT_1, 127);
rlink->command(WRITE_PORT_2, 127);
rlink->command(WRITE_PORT_3, 127);
rlink->command(WRITE_PORT_4, 127);
rlink->command(WRITE_PORT_6, 127);
rlink->command(WRITE_PORT_7, 127);
	cout << "Extend\n";
}

void arm_control::contract() {
	rlink->command(WRITE_PORT_0, 0);
	rlink->command(WRITE_PORT_1, 0);
rlink->command(WRITE_PORT_2, 0);
rlink->command(WRITE_PORT_3, 0);
rlink->command(WRITE_PORT_4, 0);
rlink->command(WRITE_PORT_6, 0);
rlink->command(WRITE_PORT_7, 0);
cout << "Contract\n";
}
