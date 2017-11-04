#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"
#include <stopwatch.h>
#include "mobility_control.hpp"

using namespace std;

mobility_control::mobility_control(robot_link* rl, line_follower* line_f) {
    rlink = rl;
    lf = line_f;
    turning_ms = 1500;  // Turning time to be calibrated
    walking_ms = 1250;  // Walking time to be calibrated
    // TODO: calibrate turn around time!
    turn_180_ms = 2000;   // constant delay time for turning around
    speed = 96;           // Marching speed
    slow_speed = 24;      // Steering speed to be calibrated
    turning_speed = 100;  // Turning speed to be calibrated
}

void mobility_control::forward() {
    rlink->command(BOTH_MOTORS_GO_OPPOSITE, speed);
}

void mobility_control::backward() {
    rlink->command(BOTH_MOTORS_GO_OPPOSITE, reversed_sign(speed));
}

void mobility_control::stop() {
    rlink->command(BOTH_MOTORS_GO_SAME, 0);
}

void mobility_control::left_sandwich() {
    while (1) {
        lf->line_following_output(rlink->request(READ_PORT_5));
        bool* lf_sensors = lf->sensor_readings;
        if ((!lf_sensors[3]) && (!lf_sensors[0])) {  //both front sensors read black
            forward();
            cout << "F" << endl;
        } else if ((!lf_sensors[3]) && lf_sensors[0]) {
            steer('R');
            cout << "R" << endl;
        } else if (lf_sensors[3] && (!lf_sensors[0])) {
            steer('L');
            cout << "L" << endl;
        } else {
            cout << "STOP" << endl;
            stop();
            break;
        }
    }
}

void mobility_control::move_till_cross() {
    while (1) {
        lf->line_following_output(rlink->request(READ_PORT_5));
        bool* lf_sensors = lf->sensor_readings;
        if ((!lf_sensors[0]) && (!lf_sensors[1])) {  //both front sensors read black
            forward();
            cout << "F" << endl;
        } else if ((!lf_sensors[0]) && lf_sensors[1]) {
            steer('R');
            cout << "R" << endl;
        } else if (lf_sensors[0] && (!lf_sensors[1])) {
            steer('L');
            cout << "L" << endl;
        } else {
            cout << "STOP" << endl;
            stop();
            break;
        }
    }
}

void mobility_control::forward_for_time_ms(int ms) {
    stopwatch watch;
    watch.start();
    while (watch.read() < ms) {
        lf->line_following_output(rlink->request(READ_PORT_5));
        bool* lf_sensors = lf->sensor_readings;
        if ((!lf_sensors[0]) && (!lf_sensors[1])) {  //both front sensors read black
            forward();
            cout << "F" << endl;
        } else if ((!lf_sensors[0]) && lf_sensors[1]) {
            steer('R');
            cout << "R" << endl;
        } else if (lf_sensors[0] && (!lf_sensors[1])) {
            steer('L');
            cout << "L" << endl;
        } else {
            cout << "STOP" << endl;
            stop();
            break;
        }
    }
    stop();
}

void mobility_control::forward_with_left_sensors(int cross_to_pass) {
    for (int i = 0; i < cross_to_pass - 1; i++) {
        left_sandwich();
        forward();
        delay(240);
    }
    left_sandwich();
    forward();
    // No delay for the last iteration
}

void mobility_control::forward_with_lf(int cross_to_pass) {
    for (int i = 0; i < cross_to_pass; i++) {
        move_till_cross();
        forward();
        delay(240);
    }
    // move_till_cross();
}

void mobility_control::turn(char direction) {
    if (direction == 'l' || direction == 'L') {
        // Turn left
        forward();
        delay(walking_ms);
        rlink->command(BOTH_MOTORS_GO_SAME, turning_speed);
        delay(turning_ms);
        while (!(0b0001 & rlink->request(READ_PORT_5)))
            ;  // Wait until the middle sensor hits the line

        rlink->command(BOTH_MOTORS_GO_SAME, 0);
    } else if (direction == 'r' || direction == 'R') {
        // Turn right
        forward();
        delay(walking_ms);
        rlink->command(BOTH_MOTORS_GO_SAME, reversed_sign(turning_speed));
        delay(turning_ms);
        while (!(0b0010 & rlink->request(READ_PORT_5)))
            ;  // Wait until the right sensor hits the line

        rlink->command(BOTH_MOTORS_GO_SAME, 0);
    }
}

void mobility_control::turn_to_left_sensors(char direction) {
    // Align to left sensors
    if (direction == 'l' || direction == 'L') {
        // Turn left
        forward();
        delay(walking_ms);
        rlink->command(BOTH_MOTORS_GO_SAME, turning_speed);
        delay(turning_ms);
        while (!(0b1000 & rlink->request(READ_PORT_5)))
            ;  // Wait until the left sensor hits the line

        rlink->command(BOTH_MOTORS_GO_SAME, 0);
    } else if (direction == 'r' || direction == 'R') {
        // Turn right
        forward();
        delay(walking_ms);
        rlink->command(BOTH_MOTORS_GO_SAME, reversed_sign(turning_speed));
        delay(turning_ms);
        while (!(0b0001 & rlink->request(READ_PORT_5)))
            ;  // Wait until the middle sensor hits the line

        rlink->command(BOTH_MOTORS_GO_SAME, 0);
    }
}

void mobility_control::steer(char direction) {
    if (direction == 'l' || direction == 'L') {
        // Steer left
        rlink->command(BOTH_MOTORS_GO_SAME, slow_speed);
    } else if (direction == 'r' || direction == 'R') {
        // Steer right
        // cout << "R " << slow_speed << endl;
        rlink->command(BOTH_MOTORS_GO_SAME, reversed_sign(slow_speed));
    }
}

void mobility_control::turn_180() {  // anti-clockwise
    rlink->command(BOTH_MOTORS_GO_SAME, turning_speed);
    delay(turn_180_ms);
    while (!(0b0001 & rlink->request(READ_PORT_5)))
        ;  // Wait until the middle sensor hits the line

    rlink->command(BOTH_MOTORS_GO_SAME, 0);
}

void mobility_control::turn_180_clockwise() {
    rlink->command(BOTH_MOTORS_GO_SAME, reversed_sign(turning_speed));
    delay(turn_180_ms);
    while (!(0b0010 & rlink->request(READ_PORT_5)))
        ;  // Wait until the right sensor hits the line

    rlink->command(BOTH_MOTORS_GO_SAME, 0);
}