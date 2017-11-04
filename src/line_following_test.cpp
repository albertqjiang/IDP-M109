#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"

#define ROBOT_NUM 7  // The id number (see below)
// robot_link rlink;         // datatype for the robot link
custom_robot_link rlink;  // Our customized robot_link class
const bool USE_STRAIN_GAUGE = false;
const bool FAILURE_RECOVERY = false;

int start(int first_ball_location_1_to_4, bool TRY_ALL_6_BALLS = false) {
    // Start collecting from the first ball location
    if (first_ball_location_1_to_4 < 1) {
        first_ball_location_1_to_4 = 1;
    } else if (first_ball_location_1_to_4 > 4) {
        first_ball_location_1_to_4 = 4;
    }
    cout << "Make sure the arm points to the balls!" << endl;
    int alignment_delay = 150;    // The delay for collection point alignment
    int arm_rotate_delay = 1000;  // The delay for the arm rotation to stop

    // Reset arm status
    rlink.ac->contract();
    rlink.ac->release();

    // Go to the location of the 1st ball
    rlink.mc->forward_with_left_sensors(1 + first_ball_location_1_to_4);
    delay(alignment_delay);
    rlink.mc->stop();
    delay(alignment_delay);

    // Reached 1st ball
    delay(1000);  // Wait for a complete stop
    rlink.ac->extend();
    rlink.ac->grab();
    rlink.ac->contract();  // 1st Ball got

    rlink.ac->goto_right_mark();
    rlink.ac->goto_right_mark();
    rlink.ac->goto_right_mark();  // 3rd slot
    delay(arm_rotate_delay);
    rlink.ac->extend();
    rlink.ac->release();
    rlink.ac->grab();  // Adjust ball position
    rlink.ac->contract();
    rlink.ac->goto_right_mark();
    delay(arm_rotate_delay);

    if (USE_STRAIN_GAUGE) {
        rlink.ac->release();
        // TODO: read strain gauge
        rlink.ac->grab();  // Strain gauge
    }
    rlink.ac->goto_right_mark();  // LDR
    delay(arm_rotate_delay);

    // Classify 1st ball
    rlink.ac->release();
    rlink.ball_slots[2] = rlink.dc->classify();  // 3rd slot
    // Faillure recovery: retry once if no ball is present
    if (FAILURE_RECOVERY && rlink.ball_slots[2] == -1) {
        // Failure recovery: attempt to collect the ball again
        for (int i = 0; i < 5; i++) {
            rlink.ac->goto_left_mark();
        }
        delay(arm_rotate_delay);
        rlink.ac->extend();
        rlink.ac->grab();
        rlink.ac->contract();  // 1st Ball got

        for (int i = 0; i < 3; i++) {  // 3rd slot
            rlink.ac->goto_right_mark();
        }
        delay(arm_rotate_delay);
        rlink.ac->extend();
        rlink.ac->release();
        rlink.ac->grab();  // Adjust ball position
        rlink.ac->contract();
        rlink.ac->goto_right_mark();
        delay(arm_rotate_delay);

        if (USE_STRAIN_GAUGE) {
            rlink.ac->release();
            // TODO: read strain gauge
            rlink.ac->grab();  // Strain gauge
        }
        rlink.ac->goto_right_mark();  // LDR
        delay(arm_rotate_delay);

        // Classify 1st ball
        rlink.ac->release();
        rlink.ball_slots[2] = rlink.dc->classify();  // 3rd slot
    }
    // End of failure recovery
    rlink.ac->grab();

    // TODO: LED output

    // Put the ball in the 3rd slot
    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();  // 3rd slot
    rlink.ac->extend();
    rlink.ac->release();  // 1st ball -> 3rd slot
    rlink.ac->contract();
    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();  // Ready to collect

    // Move to collect 2nd ball
    rlink.mc->forward_with_left_sensors(1);
    delay(alignment_delay);
    rlink.mc->stop();
    delay(alignment_delay);
    rlink.ac->extend();
    rlink.ac->grab();
    rlink.ac->contract();
    rlink.ac->goto_right_mark();
    rlink.ac->goto_right_mark();  // 2nd slot
    rlink.ac->extend();
    rlink.ac->release();
    rlink.ac->grab();  // Adjust ball position
    rlink.ac->contract();
    rlink.ac->goto_right_mark();
    rlink.ac->goto_right_mark();

    if (USE_STRAIN_GAUGE) {
        rlink.ac->release();
        // TODO: read strain gauge
        rlink.ac->grab();  // Strain gauge
    }

    rlink.ac->goto_right_mark();  // LDR

    // Classify 2nd ball
    rlink.ac->release();
    rlink.ball_slots[1] = rlink.dc->classify();  // 2nd slot
    // Faillure recovery: retry once if no ball is present
    if (FAILURE_RECOVERY && rlink.ball_slots[1] == -1) {
        // Failure recovery: attempt to collect the ball again
        for (int i = 0; i < 5; i++) {
            rlink.ac->goto_left_mark();
        }
        delay(arm_rotate_delay);
        rlink.ac->extend();
        rlink.ac->grab();
        rlink.ac->contract();  // 2nd Ball got

        for (int i = 0; i < 2; i++) {  // 2rd slot
            rlink.ac->goto_right_mark();
        }
        delay(arm_rotate_delay);
        rlink.ac->extend();
        rlink.ac->release();
        rlink.ac->grab();  // Adjust ball position
        rlink.ac->contract();
        rlink.ac->goto_right_mark();
        rlink.ac->goto_right_mark();
        delay(arm_rotate_delay);

        if (USE_STRAIN_GAUGE) {
            rlink.ac->release();
            // TODO: read strain gauge
            rlink.ac->grab();  // Strain gauge
        }
        rlink.ac->goto_right_mark();  // LDR
        delay(arm_rotate_delay);

        // Classify 1st ball
        rlink.ac->release();
        rlink.ball_slots[2] = rlink.dc->classify();  // 3rd slot
    }
    // End of failure recovery
    rlink.ac->grab();

    // TODO: LED output

    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();  // 2nd slot
    rlink.ac->extend();
    rlink.ac->release();
    rlink.ac->contract();  // 2nd ball -> 2nd slot
    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();  // Ready to collect

    // Move to collect 3rd ball
    rlink.mc->forward_with_left_sensors(1);
    delay(alignment_delay);
    rlink.mc->stop();
    delay(alignment_delay);
    rlink.ac->extend();
    rlink.ac->grab();
    rlink.ac->contract();
    rlink.ac->goto_right_mark();  // 1st slot
    rlink.ac->extend();
    rlink.ac->release();
    rlink.ac->grab();  // Adjust ball position
    rlink.ac->contract();
    rlink.ac->goto_right_mark();
    rlink.ac->goto_right_mark();
    rlink.ac->goto_right_mark();

    if (USE_STRAIN_GAUGE) {
        rlink.ac->release();
        // TODO: read strain gauge
        rlink.ac->grab();  // Strain gauge
    }

    rlink.ac->goto_right_mark();  // LDR

    // Classify 3rd ball
    rlink.ac->release();
    rlink.ball_slots[0] = rlink.dc->classify();  // 1st slot
    // Faillure recovery: retry once if no ball is present
    if (FAILURE_RECOVERY && rlink.ball_slots[1] == -1) {
        // Failure recovery: attempt to collect the ball again
        for (int i = 0; i < 5; i++) {
            rlink.ac->goto_left_mark();
        }
        delay(arm_rotate_delay);
        rlink.ac->extend();
        rlink.ac->grab();
        rlink.ac->contract();  // 3rd Ball got

        rlink.ac->goto_right_mark();
        delay(arm_rotate_delay);
        rlink.ac->extend();
        rlink.ac->release();
        rlink.ac->grab();  // Adjust ball position
        rlink.ac->contract();
        rlink.ac->goto_right_mark();
        rlink.ac->goto_right_mark();
        rlink.ac->goto_right_mark();
        delay(arm_rotate_delay);

        if (USE_STRAIN_GAUGE) {
            rlink.ac->release();
            // TODO: read strain gauge
            rlink.ac->grab();  // Strain gauge
        }
        rlink.ac->goto_right_mark();  // LDR
        delay(arm_rotate_delay);

        // Classify 1st ball
        rlink.ac->release();
        rlink.ball_slots[2] = rlink.dc->classify();  // 3rd slot
    }
    // End of failure recovery
    rlink.ac->grab();

    // TODO: LED output

    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();
    rlink.ac->goto_left_mark();  // 1st slot
    rlink.ac->extend();
    rlink.ac->release();
    rlink.ac->contract();        // 3rd ball -> 1st slot
    rlink.ac->goto_left_mark();  // Ready to collect

    // 3 balls stored here

    // Go to DR
    rlink.mc->forward_with_left_sensors(4 - first_ball_location_1_to_4);
    rlink.mc->turn('l');  // turn left, use right sensors

    // Align with DR
    rlink.mc->forward_with_lf(1);
    delay(alignment_delay);
    rlink.mc->stop();
    delay(alignment_delay);

    // Pick the 1st heavy ball (if existing) and deliver it
    rlink.drop_a_heavy_ball_to_the_right();

    // 1st DR done

    // Turn left
    rlink.mc->forward_with_lf(1);
    rlink.mc->turn_to_left_sensors('L');  // Need to align with left sensors to avoid the walls!!!

    // Go to 2nd DR and align with it
    rlink.mc->forward_with_left_sensors(1);
    rlink.mc->turn_to_left_sensors('R');  // Turn right
    rlink.mc->forward_with_left_sensors(1);
    delay(alignment_delay);
    rlink.mc->stop();
    delay(alignment_delay);

    // Pick the 1st heavy ball (if existing) and deliver it
    rlink.drop_a_heavy_ball_to_the_right();

    // Get to cross before D1 and stop
    rlink.mc->turn('l');  // Turn left
    rlink.mc->forward_with_lf(1);
    delay(alignment_delay);
    rlink.mc->stop();

    // If holding ball 1, deliver it and return to this cross, otherwise do nothing
    rlink.drop_ball_to_D123(1);
    // Go to the next cross and stop
    rlink.mc->forward_with_lf(1);
    delay(alignment_delay);
    rlink.mc->stop();

    // If holding ball 3, deliver it and return to this cross, otherwise do nothing
    rlink.drop_ball_to_D123(3);
    // Go to the next cross and stop
    rlink.mc->forward_with_lf(1);
    delay(alignment_delay);
    rlink.mc->stop();

    // If holding ball 5, deliver it and return to this cross, otherwise do nothing
    rlink.drop_ball_to_D123(5);
    // Go to the next cross and stop
    rlink.mc->forward_with_lf(1);
    delay(alignment_delay);
    rlink.mc->stop();

    // Now at the corner of the arena
    // Go home
    rlink.mc->turn('l');
    rlink.mc->forward_with_lf(4);
    rlink.mc->turn_to_left_sensors('l');

    if (!TRY_ALL_6_BALLS) {
        // End here, park the vehicle inside the box
        // TODO: park the vehicle
        return 0;
    }
    // Try the other 3 balls
    start(4, true);
}

void test_arm() {
    // Test arm and actuators
    while (1) {
        break;
        char c;
        cin >> c;
        switch (c) {
            case 'c':
                rlink.ac->contract();
                break;
            case 'e':
                rlink.ac->extend();
                break;
            case 'r':
                rlink.ac->release();
                break;
            case 'g':
                rlink.ac->grab();
                break;
            case '1':
                rlink.ac->goto_left_mark();
                break;
            case '2':
                rlink.ac->goto_right_mark();
                break;
            default:
                break;
        }
    }
}

void read_analog() {
    // Read analog input
    while (1) {
        cout << rlink.request(ADC0) << "\t";
        cout << rlink.request(ADC1) << "\t";
        cout << rlink.request(ADC2) << "\t";
        cout << rlink.request(ADC3) << "\t";
        cout << rlink.request(ADC4) << "\t";
        cout << rlink.request(ADC5) << "\t";
        cout << rlink.request(ADC6) << "\t";
        cout << rlink.request(ADC7) << endl;
        delay(100);
    }
}

void test_180_turn() {
    rlink.mc->turn_180();
    rlink.mc->forward_for_time_ms(2000);
    rlink.mc->turn_180_clockwise();
    rlink.mc->forward_for_time_ms(2000);
}

void test_D123_return() {
    rlink.mc->backward();
    delay(1000);  // TODO: calibrate how much to back the vehicle before turning around
    rlink.mc->stop();
    delay(200);
    rlink.mc->turn_180();
    rlink.mc->forward_with_lf(1);
    rlink.mc->turn('l');
}

int main() {
    // read_analog();
    // test_arm();
    // test_180_turn();
    // test_D123_return();

    start(1, false);  // Start collecting from the 1st ball, don't try all 6 balls
    // start(1, true);  // Start collecting from the 1st ball, try all 6 balls

    return 0;
}
