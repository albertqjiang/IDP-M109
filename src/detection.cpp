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

int detection::classify() {
    // return a number indicating a kind of golf ball
    // 1 - light white - D1
    // 2 - Heavy white - DR
    // 3 - Light Yellow - D2
    // 4 - Heavy Yellow - DR
    // 5 - Multi - D3
    delay(1000);  // Wait for ball to sit on LDR
    int max_reading = 0;
    for (int i = 0; i < 100; i++) {
        int current_reading = rlink->request(ADC1);
        if (max_reading < current_reading) {
            max_reading = current_reading;
        }
        delay(10);
    }

    cout << "Max reading: " << max_reading << endl;

    if (19 <= max_reading && max_reading <= 27) {
        return 4;  // Heavy Yellow
    } else if ((31 < max_reading && max_reading <= 35) || (15 < max_reading && max_reading <= 19)) {
        return 2;  // Heavy White
    } else if (56 < max_reading && max_reading <= 60) {
        return 3;  // Light yellow
    } else if (36 < max_reading && max_reading <= 46) {
        return 5;  // Multi
    } else if (62 < max_reading && max_reading <= 70) {
        return 1;  // Light White
    } else if (max_reading > 70) {
        // Failure: no ball collected or ball dropped
        return -1;
    } else {
        // Failure recovery:
        // Ball not recognized, bet it is a heavy ball
        return 2;
    }
}