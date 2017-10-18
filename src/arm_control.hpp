#ifndef ARM_CONTROL_HPP
#define ARM_CONTROL_HPP

#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>

class arm_control {
	public:
		void collect();
}
