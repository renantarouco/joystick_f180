// Copyright 2019 FURGBot


#include "manual_control.h"


ManualControl::ManualControl() : device_number_(-1), max_linear_velocity_(0), max_angular_velocity_(0), 
    running_(false), rotating_(false), dribbling_(false), kicking_(0), serial_(), robot_id_(0), pkg_id_(0),
    msg_type_(0), buffer_to_send_(vector<uint8_t>(9, 0)), axis_(vector<short>(2, 0)), 
    lua_state_(luaL_newstate()) {}


ManualControl::~ManualControl() { 
    if (lua_state_ != NULL) lua_close(lua_state_);
    this->stop();
}


void ManualControl::init() {
    luaL_openlibs(lua_state_);

    lua_pushcfunction(lua_state_, lua_CFunction(lua_kernel::joystick::newSerial));
    lua_setglobal(lua_state_, "newSerial");
    lua_pushcfunction(lua_state_, lua_CFunction(lua_kernel::joystick::f180::newJoystick));
    lua_setglobal(lua_state_, "newJoystick");

    verify_ = luaL_loadfile(lua_state_, "scripts/config.lua");
    if (verify_ != LUA_OK) lua_kernel::printError(lua_state_);
    else {
        verify_ = lua_pcall(lua_state_, 0, 0, 0);
        if (verify_ != LUA_OK) lua_kernel::printError(lua_state_); {
            lua_getglobal(lua_state_, "startConfiguration");
            verify_ = lua_pcall(lua_state_, 0, 0, 0);
            if (verify_ != LUA_OK) lua_kernel::printError(lua_state_);
        }
    }
}


void ManualControl::repeat() {
    start();
    while(1);
}


void ManualControl::start() {
    running_ = true;
    td_ = thread(&ManualControl::run, this);
}


void ManualControl::stop() {
    {
        lock_guard<mutex> lock(mu_);
        running_ = false;
    }
    td_.join();
}


void ManualControl::run() {
    bool button_send = false;
    bool axis_send = false;
    
    system_clock::time_point compair_time = high_resolution_clock::now();

    if (!joystick_->isFound()) cout << "Falha ao abrir o controle." << endl;

    while (running_) {
        if (joystick_->sample(&event_)) {
            if (event_.isButton()) button_send = readEventButton();
            else button_send = false;

            if (event_.isAxis()) readEventAxis();
        } else button_send = false;

        axis_send = verifyVelocityAxis();

        if (kicking_ >= kick_times_) {
            kicking_ = 0;
            message_.setKick(0);
            button_send = true;
        }

        if (axis_send) calculateVelocity();
        else {
            linear_velocity_x_ = 0.0;
            linear_velocity_y_ = 0.0;
        }

        if (abs(axis_[AXIS_X]) < min_axis_) axis_[AXIS_X] = 0;
        if (abs(axis_[AXIS_Y]) < min_axis_) axis_[AXIS_Y] = 0;

        if (axis_send || rotating_ || button_send || dribbling_ || kicking_) {
            if ((high_resolution_clock::now() - compair_time) >= frequency_) {
                message_.clear();
                createMessage();
                cout << message_ << endl;

                buffer_to_send_ = vector<uint8_t>(9, 0);
                message_.serialize(buffer_to_send_);
                serial_->send(buffer_to_send_);
                
                pkg_id_++;
                compair_time = high_resolution_clock::now();
            }
        }

        if(kicking_) ++kicking_;
    }

    message_.clear();
}


bool ManualControl::readEventButton() {
    switch (event_.number) {
        case A: //Low pass
            if (event_.value) {
                message_.setKick(pass_power_);
                kicking_ = 1;
            }
            break;
        case X: //Low kick
            if (event_.value) {
                message_.setKick(kick_power_);
                kicking_ = 1;
            }
            break;
        case LB: //Dribbler
            if (event_.value) message_.setDribbler(dribbler_velocity_);
            else message_.setDribbler(0);
            dribbling_ = event_.value;
            break;
        case LS: //Rotate clockwise
            if (event_.value) angular_velocity_ = static_cast<unsigned char>(max_angular_velocity_);
            else angular_velocity_ = 0.0;
            rotating_ = event_.value;
            direction_theta_ = 1;
            break;
        case RS: //Rotate counterclockwise
            if(event_.value) angular_velocity_ = static_cast<unsigned char>(max_angular_velocity_);
            else angular_velocity_ = 0.0;
            rotating_ = event_.value;
            direction_theta_ = 3;
            break;
        default:
            return false;
    }

    return event_.value;
}


void ManualControl::readEventAxis() {
    if (event_.number<axis_.size()) axis_[event_.number] = event_.value;
}


bool ManualControl::verifyVelocityAxis() {
    for (int i = 0; i < 2; i++)
        if(abs(axis_[i]) >= min_axis_) return true;
    return false;
}


void ManualControl::calculateVelocity() {
    if (axis_[AXIS_X] < 0) direction_x_ = 1;
    else direction_x_ = 3;

    if (axis_[AXIS_Y] < 0) direction_y_ = 3;
    else direction_y_ = 1;

    linear_velocity_x_ = static_cast<unsigned char>((int)(abs(axis_[AXIS_X]) * max_linear_velocity_ / max_axis_));
    linear_velocity_y_ = static_cast<unsigned char>((int)(abs(axis_[AXIS_Y]) * max_linear_velocity_ / max_axis_));
}


void ManualControl::createMessage() {
    message_.setPkgId(pkg_id_);
    message_.setMsgType(msg_type_);
    message_.setRobotId(robot_id_);
    message_.setVelocityX(linear_velocity_x_);
    message_.setVelocityY(linear_velocity_y_);
    message_.setDirectionX(direction_x_);
    message_.setDirectionY(direction_y_);
    message_.setVelocityTheta(angular_velocity_);
    message_.setDirectionTheta(direction_theta_);
}

void ManualControl::setCommunicationFrequency(int communication_frequency) { frequency_ = duration<float>(1.0/communication_frequency); }

void ManualControl::setDribblerVelocity(int dribbler_velocity) { dribbler_velocity_ = dribbler_velocity; }

void ManualControl::setKickPower(int kick_power) { kick_power_ = kick_power; }

void ManualControl::setKickTimes(int kick_times) { kick_times_ = kick_times; }

void ManualControl::setMaxAngularVelocity(int max_angular_velocity) { max_angular_velocity_ = max_angular_velocity; }

void ManualControl::setMaxAxisValue(int max_axis_value) { max_axis_ = max_axis_value; }

void ManualControl::setMaxLinearVelocity(int max_linear_velocity) { max_linear_velocity_ = max_linear_velocity; }

void ManualControl::setMinAxisValue(int min_axis_value) { min_axis_ = min_axis_value; }

void ManualControl::setMsgType(int msg_type) { msg_type_ = msg_type; }

void ManualControl::setPassPower(int pass_power) { pass_power_ = pass_power; }

void ManualControl::setRobotId(int robot_id) { robot_id_ = robot_id; }

void ManualControl::setSerialPortName(std::string serial_port_name) { serial_port_name_ = serial_port_name; }