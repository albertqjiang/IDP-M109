#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "arm_control.hpp"
#include "robot_functions.hpp"

arm_control::arm_control(robot_link* rl){
    rlink = rl;
}