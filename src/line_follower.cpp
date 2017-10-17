#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "line_follower.hpp"

using namespace std;

bool[4] line_following_output(const int port_input) {
	bool sensors[4] = {False, False, False, False};
	sensors[0] = port_input % 2 > 0;
	int place_holder = port_input / 2;
	sensors[1] = place_holder % 2 > 0;
	place_holder = place_holder / 2;
	sensors[2] = place_holder % 2 > 0;
	place_holder = place_holder / 2;
	sensors[3] = place_holder % 2 > 0;
	return sensors;
}
