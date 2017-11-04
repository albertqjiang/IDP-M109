#ifndef DETECTION_HPP
#define DETECTION_HPP

#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>

class detection {
    robot_link* rlink;

   public:
    detection(robot_link* rl);  // Ctor
    int classify();
};

#endif  // DETECTION_HPP
