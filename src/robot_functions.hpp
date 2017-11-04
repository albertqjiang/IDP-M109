#ifndef ROBOT_FUNCTIONS
#define ROBOT_FUNCTIONS

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>

// Forward declarations
class custom_robot_link;
class line_follower;
class mobility_control;
class arm_control;
// class led_control;
class detection;

#include "mobility_control.hpp"
#include "line_follower.hpp"
//#include "led_control.hpp"
#include "arm_control.hpp"
#include "detection.hpp"

int reversed_sign(const int& motor_speed);

class custom_robot_link {
   public:
    robot_link rlink;

    int ball_slots[3];  // Status of ball slots
                        // -1 for empty
                        // 1 for light W, 2 for heavy W, 3 for light Y, 4 for heavy Y, 5 for Multi

    custom_robot_link();   // Ctor
    ~custom_robot_link();  // Dtor
    int request(request_instruction instr);
    line_follower* lf;
    mobility_control* mc;
    arm_control* ac;
    //led_control* lc;
    detection* dc;

    void drop_a_heavy_ball_to_the_right();
    void drop_ball_to_D123(int ball_type);

    friend int reversed_sign(const int& motor_speed);
};

#endif
