#ifndef ARM_CONTROL_HPP
#define ARM_CONTROL_HPP

#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"

class arm_control {
    robot_link* rlink;

   public:
    arm_control(robot_link* rl);
    void extend();
    void contract();
    void collect();
};

#endif
