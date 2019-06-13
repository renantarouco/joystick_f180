// Copyright 2019 FURGBot

#ifndef JOYSTICK_SERIAL_MESSAGE_H
#define JOYSTICK_SERIAL_MESSAGE_H

#include <iostream>
#include <stdint.h>
#include <vector>

namespace furgbol {
namespace joystick {

enum SerialMessageHeaderFlags {
    ROBOT_ID, VEL_WHEEL_ONE, VEL_WHEEL_TWO, VEL_WHEEL_THREE, VEL_WHEEL_FOUR, DIRECTION, DRIBBLER, KICK
};

class SerialMessage {
    private:
        uint16_t pkg_id_;
        uint8_t msg_type_;
        uint8_t robot_id_;
        uint8_t wheels_vel_[4];
        uint8_t wheels_dir_[4]; 
        uint8_t dribbler_;
        uint8_t kick_;

    public:
        SerialMessage();
        SerialMessage(uint16_t pkg_id, uint8_t msg_type, uint8_t robot_id, uint8_t *wheels_vel, uint8_t dribbler, uint8_t kick);
        ~SerialMessage();

        void serialize(std::vector<unsigned char> &buffer);

        void clear();

        friend std::ostream &operator <<(std::ostream &, SerialMessage const &);

        void setRobotId(uint8_t id);
        void setWheelsVel(uint8_t* vel);
        void setWheelsDir(uint8_t* wheels_dir);
        void setDribbler(uint8_t dribbler);
        void setKick(uint8_t kick);

        uint16_t getPkgId();
        uint8_t getMsgType();
        uint8_t getRobotId();
        uint8_t *getWheelsVel();
        uint8_t *getWheelsDir();
        uint8_t getDribbler();
        uint8_t getKick();
};

}  // namespace joystick
}  // namespace furgbol

#endif // JOYSTICK_SERIAL_MESSAGE_H