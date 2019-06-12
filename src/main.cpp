// Copyright 2019 FURGBot

#include "serial_sender.h"

int main() {
    furgbol::joystick::SerialSender serial_sender("/dev/ttyACM0");

    uint16_t package_identification = 0;
    uint8_t message_type = 0;
    uint8_t robot_identification = 0;
    uint8_t wheels_velocity[4] = {0, 0, 0, 0};
    uint8_t dribbler = 0;
    uint8_t kick = 0;

    while (true) {
        package_identification++;
        message_type++;
        robot_identification++;
        wheels_velocity[0]++;
        wheels_velocity[1]++;
        wheels_velocity[2]++;
        wheels_velocity[3]++;
        dribbler++;
        kick++;
        serial_sender.send(furgbol::joystick::SerialMessage(package_identification, message_type, robot_identification, wheels_velocity, dribbler, kick));
    }
}