// Copyright 2019 FURGBot

#ifndef JOYSTICK_MANUAL_CONTROL_H
#define JOYSTICK_MANUAL_CONTROL_H

#include "furgbol-core/io/f180_serial_message.h"
#include "furgbol-core/io/serial_sender.h"

#include "joystick.hh"
#include "lua.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdio>
#include <chrono>


enum Axis{
    AXIS_X, AXIS_Y
};

enum Buttons {
    A = 0, X = 2, LB = 4, LS = 11, RS = 12
};

enum Directions {
    NEGATIVE = 1, POSITIVE = 3
};

enum KickType {
    NONE, PASS, KICK
};

/*!
 * \brief The ManualControl class manages a thread to read the joystick, mount the serial package, and add to the SerialCommunicator thread submission list
 */
class ManualControl {
    private:
        //Thread Variables
        bool running_; //!<Thread Execution Control Flag
        std::thread td_; //!<Class Thread
        std::mutex mu_; //!<Mutex for writing on flag running

        //Joystick Variables
        int device_number_; //!<Joystick number used by thread
        Joystick *joystick_; //!<Joystick class object to read the file where the joystick writes its data
        JoystickEvent event_; //!<JoystickEvent class object to check for joystick events that should be processed
        std::vector<short> axis_; //!<Vector holding joystick analog value

        //Control Variables
        bool rotating_; //!<Flag to indicate whether the spin button is pressed or not
        bool dribbling_; //!<Flag to indicate if the dribbler button is pressed or not
        int kicking_; //!<Variable to ensure that the robot will attempt to kick kick_times_ to facilitate kick control
        uint8_t linear_velocity_x_; //!<Variable that stores the linear velocity in x axis
        uint8_t linear_velocity_y_; //!<Variable that stores the linear velocity in y axis
        uint8_t angular_velocity_; //!<Variable that keeps the angular velocity
        uint8_t direction_x_; //!<Variable that keeps the direction of linear velocity in x axis
        uint8_t direction_y_; //!<Variable that keeps the linear velocity direction in y axis
        uint8_t direction_theta_; //!<Variable that keeps the direction of angular velocity
        int kick_type_; //!<Variable that stores kick type

        //Parameters
        uint8_t msg_type_; //!<Type of the message
        int robot_id_; //!<Variable that holds the id of the robot to be controlled
        int max_linear_velocity_; //!<Maximum linear speed the robot can assume
        int max_angular_velocity_; //!<Maximum angular velocity the robot can assume
        int dribbler_velocity_; //!<Dribbler speed in pwm
        int kick_power_; //!<Kick strength in pwm
        int pass_power_; //!<Pass strength in pwm
        int max_axis_; //!<Variable to store the maximum value read by the axis
        int min_axis_; //!<Variable to store the minimum value read by the axis
        int kick_times_; //!<Variable to store the number of times the robot will try to kick
        std::chrono::duration<float> frequency_; //!<Variable to store the transmission frequency

        //Networking
        furgbol::io::F180SerialMessage message_; //!<Message to be sent
        furgbol::io::SerialSender *serial_; //!<Pointer to the serial communication thread
        uint16_t pkg_id_; //!<Package id
        std::vector<uint8_t> buffer_to_send_; //!<Buffer to be sent as message

        //Lua
        lua_State *lua_state_; //!<Lua state object

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
        /*!
        * \brief createMessage constructs the message_
        */
        void createMessage();

    public:
        ManualControl();
        ~ManualControl();

        /*!
        * \brief init configures the joystick
        */
        void init();
        /*!
        * \brief repeat locks the execution
        */
        void repeat();
        /*!
        * \brief start sets the running flag to true and rebuilds thread td to restart the thread
        */
        void start();
        /*!
        * \brief stop hangs with mutex, set running flag to false and join in thread td
        */
        void stop();

        //Setters
        void setSerialPort(std::string serial_port_name);
        void setMsgType(int msg_type);
        void setRobotId(int robot_id);
        void setCommunicationFrequency(int communication_frequency);
        void setMinAxisValue(int min_axis_value);
        void setMaxAxisValue(int max_axis_value);
        void setMaxLinearVelocity(int max_linear_velocity);
        void setMaxAngularVelocity(int max_angular_velocity);
        void setDribblerVelocity(int dribbler_velocity);
        void setKickPower(int kick_power);
        void setKickTimes(int kick_times);
        void setPassPower(int pass_power);
};

#endif // JOYSTICK_MANUAL_CONTROL_H