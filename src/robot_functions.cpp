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
    dc = new detection(&rlink);
    // TODO: Initialize more subclasses

    // Initialize status of ball slots
    ball_slots[0] = -1;
    ball_slots[1] = -1;
    ball_slots[2] = -1;
    // -1 for empty
    // 1 for light W, 2 for heavy W, 3 for light Y, 4 for heavy Y, 5 for Multi
}

custom_robot_link::~custom_robot_link() {
    delete lf;
    delete mc;
    delete ac;
    delete dc;
}

int custom_robot_link::request(request_instruction instr) {
    return rlink.request(instr);
}

void custom_robot_link::drop_a_heavy_ball_to_the_right() {
    int heavy_ball_slot = -1;
    for (int i = 0; i < 3; i++) {
        if (ball_slots[i] == 2 || ball_slots[i] == 4) {
            heavy_ball_slot = i;  // 1st heavy ball
            ball_slots[i] = -1;   // Clear ball slot
            break;
        }
    }

    if (heavy_ball_slot >= 0) {  // Has heavy ball(s), deliver 1st heavy ball
        // Go to 1st heavy ball
        for (int i = 0; i < heavy_ball_slot + 1; i++) {
            // Distance between delivery position and slot is 1 + heavy_ball_slot
            ac->goto_right_mark();
        }

        // Grab ball
        ac->extend();
        ac->grab();
        ac->contract();

        // Go back to delivery position
        for (int i = 0; i < heavy_ball_slot + 1; i++) {
            // Distance between delivery position and slot is 1 + heavy_ball_slot
            ac->goto_right_mark();
        }

        // Release ball
        ac->extend();
        ac->release();
        ac->contract();
    }
}
