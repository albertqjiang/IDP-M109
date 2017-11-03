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
    int precision_speed;  // Speed for precision arm rotation control
    int leave_delay;	  // Delay for the arm to leave the current position
    int actuator_delay;   // Delay for the actuator to finish one operation
    bool read_paper_sensor(); // Read the IR sensor of the arm

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

    // Precision rotation
    void goto_left_mark();
    void goto_right_mark();

    friend int reversed_sign(const int& motor_speed);
};

#endif
