// Copyright 2019 FURGBot

#ifndef JOYSTICK_SERIAL_MESSAGE_H
#define JOYSTICK_SERIAL_MESSAGE_H

#include <iostream>
#include <stdint.h>
#include <vector>

namespace furgbol {
namespace joystick {

/*!
 * \brief The SerialMessageHeaderFlags enum defines flags to handle the buffer
 */
enum SerialMessageHeaderFlags {
    ROBOT_ID = 0, VEL_X = 1, VEL_Y = 2, VEL_THETA = 3, DIR_X = 4, DIR_Y = 5, DIR_THETA = 6, 
    DRIBBLER = 7, KICK = 8
};

/*!
 * \brief The SerialMessage class is for storing protocol attributes separately and then preparing them for submission
 */
class SerialMessage {
    private:
        uint16_t pkg_id_; //!<Store the package identifier
        uint8_t msg_type_; //!<Describes the type of message
        uint8_t robot_id_; //!<Stores the robot identifier
        uint8_t velocity_x_; //!<X-axis linear velocity in pwm
        uint8_t velocity_y_; //!<Y-axis linear velocity in pwm
        uint8_t velocity_theta_; //!<Angular velocity in pwm
        uint8_t direction_x_; //!<X-axis linear velocity direction
        uint8_t direction_y_; //!<Y-axis linear velocity direction
        uint8_t direction_theta_; //!<Angular velocity direction
        uint8_t dribbler_; //!<Dribbler velocity in pwm
        uint8_t kick_; //!<Kick power in pwm

    public:
        SerialMessage();
        ~SerialMessage();

        /*!
         * \brief serialize prepares packet in buffer to be sent
         */
        void serialize(std::vector<uint8_t> &buffer);

        /*!
         * \brief clear clears all message attributes
         */
        void clear();

        //Stream to print the message
        friend std::ostream &operator <<(std::ostream &, SerialMessage const &);

        //Setters
        void setRobotId(uint8_t robot_id);
        void setVelocityX(uint8_t velocity_x);
        void setVelocityY(uint8_t velocity_y);
        void setVelocityTheta(uint8_t velocity_theta);
        void setDirectionX(uint8_t direction_x);
        void setDirectionY(uint8_t direction_y);
        void setDirectionTheta(uint8_t direction_theta);
        void setDribbler(uint8_t dribbler);
        void setKick(uint8_t kick);

        //Getters
        uint16_t getPkgId();
        uint8_t getMsgType();
        uint8_t getRobotId();
        uint8_t getVelocityX();
        uint8_t getVelocityY();
        uint8_t getVelocityTheta();
        uint8_t getDirectionX();
        uint8_t getDirectionY();
        uint8_t getDirectionTheta();
        uint8_t getDribbler();
        uint8_t getKick();
};

}  // namespace joystick
}  // namespace furgbol

#endif // JOYSTICK_SERIAL_MESSAGE_H