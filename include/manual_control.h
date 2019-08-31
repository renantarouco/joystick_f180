// Copyright 2019 FURGBot

#ifndef JOYSTICK_MANUAL_CONTROL_H
#define JOYSTICK_MANUAL_CONTROL_H

#include "serial_message.h"
#include "serial_sender.h"
#include "parameters.h"

#include "joystick.hh"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdio>
#include <chrono>

using namespace std;
using namespace furgbol::joystick;
using namespace furgbol::parameters;
using namespace std::chrono;

enum Axis{
    AXIS_X, AXIS_Y
};

enum Buttons {
    A = 0, X = 2, LB = 4, LS = 11, RS = 12
};

/*!
 * \brief The ManualControl class manages a thread to read the joystick, mount the serial package, and add to the SerialCommunicator thread submission list
 */
class ManualControl {
    private:
        //Thread Variables
        bool running_; //!<Thread Execution Control Flag
        thread td_; //!<Class Thread
        mutex mu_; //!<Mutex for writing on flag running

        //Joystick Variables
        int device_number_; //!<Joystick number used by thread
        Joystick *joystick_; //!<Joystick class object to read the file where the joystick writes its data
        JoystickEvent event_; //!<JoystickEvent class object to check for joystick events that should be processed
        vector<short> axis_; //!<Vector holding joystick analog value

        //Control Variables
        int robot_id_; //!<Variable that holds the id of the robot to be controlled
        bool rotating_; //!<Flag to indicate whether the spin button is pressed or not
        bool dribbling_; //!<Flag to indicate if the dribbler button is pressed or not
        int kicking_; //!<Variable to ensure that the robot will attempt to kick kick_times_ to facilitate kick control
        int linear_velocity_x_; //!<Variable that stores the linear velocity in x axis
        int linear_velocity_y_; //!<Variable that stores the linear velocity in y axis
        int angular_velocity_; //!<Variable that keeps the angular velocity
        int direction_x_; //!<Variable that keeps the direction of linear velocity in x axis
        int direction_y_; //!<Variable that keeps the linear velocity direction in y axis
        int direction_theta_; //!<Variable that keeps the direction of angular velocity

        //Parameters
        int max_linear_velocity_; //!<Maximum linear speed the robot can assume
        int max_angular_velocity_; //!<Maximum angular velocity the robot can assume
        int dribbler_velocity_; //!<Dribbler speed in pwm
        int kick_power_; //!<Kick strength in pwm
        int pass_power_; //!<Pass strength in pwm
        int max_axis_; //!<Variable to store the maximum value read by the axis
        int min_axis_; //!<Variable to store the minimum value read by the axis
        int kick_times_; //!<Variable to store the number of times the robot will try to kick
        duration<float> frequency_; //!<Variable to store the transmission frequency

        //Networking
        SerialMessage message_; //!<Message to be sent
        SerialSender *serial_; //!<Pointer to the serial communication thread

        /*!
         * \brief calculateVelocity calculates the linear velocity of the robot based on the value offered by the axis vector
         */
        void calculateVelocity();

        /*!
         * \brief readEventButton processes an event that is triggered by a button, checking what type of action to take 
         * \return boolean indicating whether or not to send data to the robot
         */
        bool readEventButton();

        /*!
        * \brief readEventAxis processes an event that is triggered by an analog, filling the axis vector
        */
        void readEventAxis();

        /*!
        * \brief verifyVelocityAxis checks if the values in the axis vector are sufficient to calculate the velocity
        * \return boolean indicating whether the data is relevant or not
        */
        bool verifyVelocityAxis();

        /*!
        * \brief run is the main loop to thread, passed by parameter to td
        */
        void run();

    public:
        ManualControl();
        ManualControl(int device_number, Parameters param, SerialSender *serial);

        ~ManualControl();

        /*!
        * \brief start sets the running flag to true and rebuilds thread td to restart the thread
        */
        void start();
        /*!
        * \brief stop hangs with mutex, set running flag to false and join in thread td
        */
        void stop();
};

#endif // JOYSTICK_MANUAL_CONTROL_H