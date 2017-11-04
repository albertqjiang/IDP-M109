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
const bool TRY_ALL_6_BALLS = false;

int start() {
    // Start route testing
    // Collect first ball
    cout << "Make sure the arm points to the balls!" << endl;
    int alignment_delay = 150;    // The delay for collection point alignment
    int arm_rotate_delay = 1000;  // The delay for the arm rotation to stop

    // Reset arm status
    rlink.ac->contract();
    rlink.ac->release();

    // Go to 1st ball
    rlink.mc->forward_with_left_sensors(2);
    delay(alignment_delay);
    rlink.mc->stop();
    delay(alignment_delay);

    // Reached 1st ball
    rlink.ac->extend();
    rlink.ac->release();
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
    rlink.mc->forward_with_left_sensors(3);
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
    forward_with_lf(4);
    rlink.mc->turn_to_left_sensors('l');
    
    if (!TRY_ALL_6_BALLS) {
        // End here, park the vehicle inside the box
        // TODO: park the vehicle
        return 0;
    }
    // Try all 6 balls, continue

    /*
    // Move to collect third ball
    rlink.ac->contract();
    rlink.ac->goto_left_mark();
    rlink.ac->right(190);
    delay(1000);
    rlink.mc->forward_with_left_sensors(1);
    rlink.mc->stop();
    rlink.ac->extend();
    rlink.ac->grab();
    rlink.ac->contract();
    rlink.ac->goto_right_mark();
    rlink.ac->goto_right_mark();
    rlink.ac->goto_right_mark();
    rlink.ac->left(190);
    delay(1000);
    rlink.ac->extend();
	rlink.ac->release();
	*/
}

void test_actuator() {
    // Test actuator
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

int main() {
    cout << "go" << endl;
    rlink.ac->contract();
    rlink.ac->release();
    rlink.ac->grab();
    rlink.ac->extend();
    rlink.rlink.command(MOTOR_3_GO, (60));
    delay(800);
    return 0;
    // read_analog(); return 0;
    // start();
    /*
	rlink.mc->forward_with_left_sensors(1);
	delay(150);
	rlink.mc->stop();
	char c; cin >> c;
	rlink.mc->turn('L');
	rlink.mc->forward_with_lf(1);
	rlink.mc->stop();
	cin >> c;
	rlink.mc->forward_with_lf(1);
	rlink.mc->turn_to_left_sensors('L');
	*/
    rlink.mc->forward_with_left_sensors(1);
    rlink.mc->turn_to_left_sensors('R');
    rlink.mc->forward_with_left_sensors(1);
    rlink.mc->turn('L');
    rlink.mc->forward_with_lf(1);
    rlink.mc->turn('L');
    rlink.mc->forward_with_lf(1);
    return 0;

    /*	// Arm rotor testing
	rlink.ac->contract();
	rlink.ac->release();
	while (1) {
		cout << "Go right" << endl;
		int num_of_marks = 7;
		while (num_of_marks--) {
			rlink.ac->extend();
			rlink.ac->release();
			rlink.ac->grab();
			rlink.ac->contract();
			rlink.ac->goto_right_mark();
			rlink.ac->left(190);
			delay(1000);
		}
		
		cout << "Go left" << endl;
		num_of_marks = 7;
		while (num_of_marks--) {
			rlink.ac->extend();
			rlink.ac->release();
			rlink.ac->grab();
			rlink.ac->contract();
			rlink.ac->goto_left_mark();
			rlink.ac->right(180);
			delay(1000);
		}
	}
	return 0;
*/
    /*while(1) {
		//rlink.mc->turn('l'); break;
		rlink.lf->line_following_output(rlink.request(READ_PORT_5));
		bool* lf_sensors = rlink.lf->sensor_readings;
		int rota_speed = 75 + 128;
		if (!lf_sensors[2]) { //both front sensors read black
			rlink.rlink.command(MOTOR_3_GO, rota_speed);
		}
		else {
			rlink.rlink.command(MOTOR_3_GO, rota_speed-128);
			delay(500);
			break;
		}
		
		
	}
	return 0;*/

    // Go around the table

    rlink.mc->forward_with_lf(1);
    for (int i = 0; i < 10; i++) {
        rlink.mc->forward_with_lf(6);
        rlink.mc->turn('L');
        rlink.mc->forward_with_lf(2);
        rlink.mc->turn('L');
        rlink.mc->forward_with_lf(1);
        rlink.mc->turn('R');
        rlink.mc->forward_with_lf(1);
        rlink.mc->turn('L');
        rlink.mc->forward_with_lf(4);
        rlink.mc->turn('L');
        rlink.mc->forward_with_lf(4);
        rlink.mc->turn('L');
    }
    return 0;

    // Actuator testing
    rlink.ac->contract();
    rlink.ac->release();
    delay(2000);
    while (1) {
        int to_slot_0 = 1500;

        rlink.ac->right(to_slot_0);  // Turn right for to_slot_0 ms.
        delay(2000);
        rlink.ac->left(to_slot_0);  // Turn left for to_slot_0 ms.
        cout << "Stop\n";
        delay(2000);
    }
    return 0;

    // Line following and turning testing
    while (1) {
        //rlink.mc->turn('l'); break;
        rlink.lf->line_following_output(rlink.request(READ_PORT_5));
        bool* lf_sensors = rlink.lf->sensor_readings;
        if ((!lf_sensors[0]) && (!lf_sensors[1])) {  //both front sensors read black
            rlink.mc->forward();
            cout << "F" << endl;
        } else if ((!lf_sensors[0]) && lf_sensors[1]) {
            rlink.mc->steer('R');
            cout << "R" << endl;
        } else if (lf_sensors[0] && (!lf_sensors[1])) {
            rlink.mc->steer('L');
            cout << "L" << endl;
        } else {
            cout << "STOP" << endl;
            rlink.mc->stop();
            break;
        }
    }
    rlink.mc->turn('R');
    while (1) {
        //rlink.mc->turn('l'); break;
        rlink.lf->line_following_output(rlink.request(READ_PORT_5));
        bool* lf_sensors = rlink.lf->sensor_readings;
        if ((!lf_sensors[0]) && (!lf_sensors[1])) {  //both front sensors read black
            rlink.mc->forward();
            cout << "F" << endl;
        } else if ((!lf_sensors[0]) && lf_sensors[1]) {
            rlink.mc->steer('R');
            cout << "R" << endl;
        } else if (lf_sensors[0] && (!lf_sensors[1])) {
            rlink.mc->steer('L');
            cout << "L" << endl;
        } else {
            cout << "STOP" << endl;
            rlink.mc->stop();
            break;
        }
    }

    return 0;
}
