#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"

#define ROBOT_NUM 7       // The id number (see below)
// robot_link rlink;         // datatype for the robot link
custom_robot_link rlink;  // Our customized robot_link class
double PARAMETER_TO_CALIBRATE = 1.0;

int main() {
	// Arm rotor testing
	/* while (1) {
		cout << "Go right" << endl;
		rlink.ac->goto_right_mark();
		delay(1000);
		rlink.ac->goto_right_mark();
		delay(1000);
		rlink.ac->goto_right_mark();
		delay(1000);
		rlink.ac->goto_right_mark();
		delay(1000);
		rlink.ac->goto_right_mark();
		delay(1000);
		
		cout << "Go left" << endl;
		rlink.ac->goto_left_mark();
		delay(1000);
		rlink.ac->goto_left_mark();
		delay(1000);
		rlink.ac->goto_left_mark();
		delay(1000);
		rlink.ac->goto_left_mark();
		delay(1000);
		rlink.ac->goto_left_mark();
		delay(1000);
	}
	return 0;*/
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

	// Read analog input
	while(1) {
	// cout<<"Analog input"<<endl;
	cout<<rlink.request (ADC0)<<"\t";
	cout<<rlink.request (ADC1)<<"\t";
	cout<<rlink.request (ADC2)<<"\t";
	cout<<rlink.request (ADC3)<<"\t";
	cout<<rlink.request (ADC4)<<"\t";
	cout<<rlink.request (ADC5)<<"\t";
	cout<<rlink.request (ADC6)<<"\t";
	cout<<rlink.request (ADC7)<<endl;
	delay(100);
	}

	// Go around the table
	/*
	rlink.mc->forward_with_lf(1);
	for (int i = 0; i <10; i++) {
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
	*/
	
	// TODO: The rotation motor can't be calibrated due to crazy resistance forces of the wires.
	// TODO: need softer wires and better wire arrangement
	// Actuator testing
	rlink.ac->contract();
	rlink.ac->release();
	delay(2000);
	while (1) {
		int to_slot_0 = 1500;
		
		rlink.ac->right(to_slot_0); // Turn right for to_slot_0 ms.
		delay(2000);
		rlink.ac->left(to_slot_0); // Turn left for to_slot_0 ms.
		cout << "Stop\n";
		delay(2000);
	}
	return 0;

	// Line following and turning testing
	while(1) {
		//rlink.mc->turn('l'); break;
		rlink.lf->line_following_output(rlink.request(READ_PORT_5));
		bool* lf_sensors = rlink.lf->sensor_readings;
		if ((!lf_sensors[0]) && (!lf_sensors[1])) { //both front sensors read black
			rlink.mc->forward();
			cout << "F" << endl;
		}
		else if ((!lf_sensors[0]) && lf_sensors[1]) {
			rlink.mc->steer('R');
			cout << "R" << endl;
		}
		else if (lf_sensors[0] && (!lf_sensors[1])) {
			rlink.mc->steer('L');
			cout << "L" << endl;
		}
		else {
			cout << "STOP" << endl;
			rlink.mc->stop();
			break;
		}
		
	}
	rlink.mc->turn('R');
	while(1) {
		//rlink.mc->turn('l'); break;
		rlink.lf->line_following_output(rlink.request(READ_PORT_5));
		bool* lf_sensors = rlink.lf->sensor_readings;
		if ((!lf_sensors[0]) && (!lf_sensors[1])) { //both front sensors read black
			rlink.mc->forward();
			cout << "F" << endl;
		}
		else if ((!lf_sensors[0]) && lf_sensors[1]) {
			rlink.mc->steer('R');
			cout << "R" << endl;
		}
		else if (lf_sensors[0] && (!lf_sensors[1])) {
			rlink.mc->steer('L');
			cout << "L" << endl;
		}
		else {
			cout << "STOP" << endl;
			rlink.mc->stop();
			break;
		}
		
	}

	return 0;
}

