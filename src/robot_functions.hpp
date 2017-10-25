#ifndef ROBOT_FUNCTIONS
#define ROBOT_FUNCTIONS

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "mobility_control.hpp"
#include "line_follower.hpp"
//#include "led_control.hpp"
#include "arm_control.hpp"
#include "detection.hpp"

int reversed_sign(const int& motor_speed);

class custom_robot_link {
    robot_link rlink;

   public:
    custom_robot_link();  // Ctor
    line_follower lf;
    mobility_control mc;
    arm_control ac;
    //led_control lc;
    detection det;

    friend int reversed_sign(const int& motor_speed);
};

#endif
