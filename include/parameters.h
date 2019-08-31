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

/*!
 * \brief The Parameters class handles the parameters that are passed by .json
 */
class Parameters {
    public:
        int min_axis; //!<Minimal axis value accepted
        int max_axis; //!<Maximal axis value accepted
        int max_linear_velocity; //!<Maximal linear velocity accepted
        int max_angular_velocity; //!<Maximal angular velocity accepted
        int dribbler_velocity; //!<Maximal dribbler velocity accepted
        int kick_power; //!<Robot kick strenght
        int kick_times; //!<Number of times the robot tries to kick
        int pass_power; //!<Robot pass strength

        int robot_id; //!<ID of the robot that will be controlled

        std::string serial_port; //!<Address of the serial port that will be used
        int frequency; //!<Frequency in Hz of packet sending

        Parameters();
        ~Parameters();

        /*!
         * \brief readParameters reads the .json file and assigns the values to its variables
         */
        void readParameters();
};

}  // namespace paramaters
}  // namespace furgbol

#endif // JOYSTICK_PARAMETERS_H