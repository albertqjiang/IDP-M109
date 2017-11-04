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
    // TODO: Initialize led_control

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

void custom_robot_link::drop_ball_to_D123(int ball_type) {
    // If holding target ball, go to delivery point, drop it and return
    // Start at the cross before D1, D2 or D3, which should be to the left of the robot

    int target_slot = -1;
    for (int i = 0; i < 3; i++) {
        if (ball_slots[i] == ball_type) {
            target_slot = i;     // target ball
            ball_slots[i] = -1;  // Clear ball slot
            break;
        }
    }

    if (target_slot >= 0) {  // Has target ball, deliver 1st heavy ball
        // Go to delivery point first
        mc->turn('L');

        // TODO: calibrate time to hit D1-3!!!
        mc->forward_for_time_ms(5000);
        // TODO!!!!

        // Rotate to target ball
        for (int i = 0; i < target_slot + 1; i++) {
            // Distance to the target slot is 1 + target_slot
            ac->goto_right_mark();
        }

        // Grab ball
        ac->extend();
        ac->grab();
        ac->contract();

        // Rotate back to delivery position in the front
        for (int i = 0; i < target_slot + 2; i++) {
            // Distance between delivery position and slot is 2 + target_slot
            ac->goto_right_mark();
        }

        // Release ball (when contracted)
        ac->release();

        // Reset to original arm position
        ac->goto_right_mark();

        // Now return to the cross, and face the next cross
        mc->backward();
        delay(1000);  // TODO: calibrate how much to back the vehicle before turning around
        mc->stop();
        delay(200);
        mc->turn_180();
        mc->forward_with_lf(1);
        mc->turn('l');
    }
}
