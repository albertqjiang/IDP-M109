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
    int rot_speed;

   public:
    arm_control(robot_link* rl);

    // Actuator control
    void extend();
    void contract();
    void grab();
    void release();

    // Rotation control
    void right(int ms);
    void left(int ms);

    friend int reversed_sign(const int& motor_speed);
};

#endif
