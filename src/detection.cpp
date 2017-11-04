#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "detection.hpp"

detection::detection(robot_link* rl) {
    rlink = rl;
}