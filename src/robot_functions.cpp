#include <iostream>
#include <cstdlib>  // For exit()
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"
using namespace std;

#define ROBOT_NUM 7  // The id number (see below)

int reversed_sign(const int& motor_speed) {
    // cout << motor_speed << " " << (0b10000000 ^ motor_speed) << endl;
    return 0b10000000 ^ motor_speed;
}

custom_robot_link::custom_robot_link() {
    // Ctor
    int val;  // data from microprocessor
#ifdef __arm__
    if (!rlink.initialise("127.0.0.1")) {  // setup for local microcontroller
#else
    if (!rlink.initialise(ROBOT_NUM)) {  // setup for Wi-Fi communication
#endif
        cout << "Cannot initialise link" << endl;
        rlink.print_errs("    ");
    }
    val = rlink.request(TEST_INSTRUCTION);  // send test instruction
    if (val == TEST_INSTRUCTION_RESULT) {   // check result
        cout << "Test passed" << endl;
        // all OK, finish
    } else if (val == REQUEST_ERROR) {
        cout << "Fatal errors on link:" << endl;
        rlink.print_errs();
    } else {
        cout << "Test failed (bad value returned)" << endl;
        exit(1);  // error, finish
    }

    // Initialize all subclasses
    lf = new line_follower(&rlink);
    mc = new mobility_control(&rlink, lf);
    ac = new arm_control(&rlink);
    // TODO: Initialize more subclasses
}

custom_robot_link::~custom_robot_link() {
    delete lf;
    delete mc;
    delete ac;
}

int custom_robot_link::request(request_instruction instr) {
    return rlink.request(instr);
}
