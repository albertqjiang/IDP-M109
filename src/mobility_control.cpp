#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"
#include "mobility_control.hpp"

using namespace std;

mobility_control::mobility_control(robot_link* rl, line_follower* line_f) {
    rlink = rl;
    lf = line_f;
    turning_ms = 1500;    // Turning time to be calibrated
    walking_ms = 1250;    // Walking time to be calibrated
    u_turn_ms = 2000;     // u_turn constant delay time
    speed = 96;           // Marching speed
    slow_speed = 24;      // Steering speed to be calibrated
    turning_speed = 100;  // Turning speed to be calibrated
}

void mobility_control::forward() {
    rlink->command(BOTH_MOTORS_GO_OPPOSITE, speed);
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

    /* lf->line_following_output(rlink->request(READ_PORT_5));
    while (!(lf->sensor_readings[0] && lf->sensor_readings[1])) {
        // Unless both front sensors detect white, repeat doing this
        if ((!lf->sensor_readings[0]) && (!lf->sensor_readings[1])) {
            // Both front sensors are black
            // rlink->command(BOTH_MOTORS_GO_SAME, speed);
            // TODO: failure recovery
        }

        else if ((!lf->sensor_readings[0]) && (lf->sensor_readings[1])) {
            // Left motor is black and right motor is white
            // Steer right
            // rlink->command(BOTH_MOTORS_GO_OPPOSITE, slow_speed);
            steer('R');
        }

        else if ((lf->sensor_readings[0]) && (!lf->sensor_readings[1])) {
            // Left motor is white and right motor is black
            // Steer left
            // rlink->command(BOTH_MOTORS_GO_OPPOSITE, reversed_sign(slow_speed));
            steer('L');
        }
        lf->line_following_output(rlink->request(READ_PORT_5));
    }*/
}

void mobility_control::move_across_cross() {
    lf->line_following_output(rlink->request(READ_PORT_5));
    while (lf->sensor_readings[0] || lf->sensor_readings[1]) {
        if ((lf->sensor_readings[0]) && (lf->sensor_readings[1])) {
            // Go forward
            rlink->command(BOTH_MOTORS_GO_OPPOSITE, speed);
        } else if ((!lf->sensor_readings[0]) && (lf->sensor_readings[1])) {
            // Left motor is black and right motor is white
            // Steer left
            // rlink->command(BOTH_MOTORS_GO_OPPOSITE, slow_speed);
            steer('L');
        }

        else if ((lf->sensor_readings[0]) && (!lf->sensor_readings[1])) {
            // Left motor is white and right motor is black
            // Steer right
            // rlink->command(BOTH_MOTORS_GO_OPPOSITE, reversed_sign(slow_speed));
            steer('R');
        }
        lf->line_following_output(rlink->request(READ_PORT_5));
    }
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
        while (!(0b0100 & rlink->request(READ_PORT_5)))
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

void mobility_control::demo_start_and_align_ball(int ball_num) {
    forward_with_lf(ball_num);  // TODO: Adapt to the playground
    turn('R');
    forward();
    delay(1000);  // TODO: calibrate the time
    stop();
}

void mobility_control::u_turn() {
    rlink->command(BOTH_MOTORS_GO_SAME, turning_speed);
    delay(u_turn_ms);
    while (!(0b0001 & rlink->request(READ_PORT_5)))
        ;  // Wait until the middle sensor hits the line

    rlink->command(BOTH_MOTORS_GO_SAME, 0);
}