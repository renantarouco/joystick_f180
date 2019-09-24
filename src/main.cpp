// Copyright 2019 FURGBot

#include "furgbol-core/io/serial_sender.h"
#include "manual_control.h"

int main() {
    furgbol::parameters::Parameters param;

    furgbol::io::SerialSender serial_sender(param.serial_port);

    ManualControl joystick(0, param, &serial_sender);

    joystick.start();

    while(1);
}