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
        turning_ms = 1800;  // Turning time to be calibrated
	walking_ms = 1400;  // Walking time to be calibrated
	speed = 96;        // Marching speed
	slow_speed = 24;    // Steering speed to be calibrated
	turning_speed = 100;// Turning speed to be calibrated
}

void mobility_control::forward() {
    rlink->command(BOTH_MOTORS_GO_OPPOSITE, speed);
}

void mobility_control::stop() {
    rlink->command(BOTH_MOTORS_GO_SAME, 0);
}

void mobility_control::move_till_cross() {
	while (1) {
		lf->line_following_output(rlink->request(READ_PORT_5));
		bool* lf_sensors = lf->sensor_readings;
		if (lf_sensors[0] && lf_sensors[1]) { //both front sensors read black
			forward();
		}
		else if ((!lf_sensors[0]) && lf_sensors[1]) {
			steer('R');
		}
		else if (lf_sensors[0] && (!lf_sensors[1])) {
			steer('L');
		}
		else {
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

void mobility_control::forward_with_lf(int cross_to_pass) {
    for (int i = 0; i < cross_to_pass; i++) {
        move_till_cross();
        move_across_cross();
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
        rlink->command(BOTH_MOTORS_GO_SAME, 0);
    } else if (direction == 'r' || direction == 'R') {
        // Turn right
        forward();
        delay(walking_ms);
        rlink->command(BOTH_MOTORS_GO_SAME, reversed_sign(turning_speed));
        delay(turning_ms);
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
