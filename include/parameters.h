// Copyright 2019 FURGBot

#ifndef JOYSTICK_PARAMETERS_H
#define JOYSTICK_PARAMETERS_H

#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>
#include <json.hpp>

namespace furgbol {
namespace parameters {

class Parameters {
    public:
        int min_axis;
        int max_axis;
        int max_linear_velocity;
        int max_angular_velocity;
        int dribbler_velocity;
        int kick_power;
        int kick_times;
        int pass_power;

        int robot_id;

        std::string serial_port;
        int frequency;

        Parameters();
        ~Parameters();

        void read_parameters();
};

}  // namespace paramaters
}  // namespace furgbol

#endif // JOYSTICK_PARAMETERS_H