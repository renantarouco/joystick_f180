// Copyright 2019 FURGBot

#include "furgbol-core/io/serial_sender.h"
#include "manual_control.h"

int main() {
    ManualControl joystick();
    joystick.init();
    joystick.repeat();
    while(1);
}