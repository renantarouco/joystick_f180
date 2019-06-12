// Copyright 2019 FURGBot

#include "serial_sender.h"

#include <string>

namespace furgbol {
namespace joystick {

SerialSender::SerialSender(std::string serial_port_name) : io_service_(), serial_port_(io_service_), buffer_(buf_.data()) {
    serial_port_.open(serial_port_name);
}

SerialSender::~SerialSender() {
    serial_port_.close();
}

void SerialSender::send(SerialMessage message_to_send) {
    message_to_send.serialize(buffer_to_send_);
    std::ostream os(&buf_);
    os.write(buffer_to_send_, 32);
    buffer_ = buf_.data();
    serial_port_.write_some(buffer_);
}

} // namespace joystick
} // namespace furgbol