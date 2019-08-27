// Copyright 2019 FURGBot

#include "manual_control.h"

ManualControl::ManualControl() : device_number_(-1), max_linear_velocity_(0), max_angular_velocity_(0), running_(false), rotating_(false), dribbling_(false), kicking_(0), serial_(), bonus_linear_velocity_(0), robot_id_(0) {
    axis_ = vector<short>(2, 0);

    message_.setRobotId(robot_id_);
}

ManualControl::ManualControl(int device_number, Parameters param, SerialSender *serial) 
    : device_number_(device_number), max_linear_velocity_(param.max_linear_velocity),
    max_angular_velocity_(param.max_angular_velocity), running_(false), rotating_(false),
    dribbling_(false), kicking_(0), serial_(serial), bonus_linear_velocity_(param.bonus_linear_velocity),
    robot_id_(param.robot_id), max_axis_(param.max_axis), min_axis_(param.min_axis), kick_times_(param.kick_times),
    dribbler_velocity_(param.dribbler_velocity), kick_power_(param.kick_power), pass_power_(param.pass_power)
{
    joystick_ = new Joystick(device_number);

    axis_ = vector<short>(2, 0);

    message_.setRobotId(robot_id_);
}

ManualControl::~ManualControl() {
    this->stop();
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
            button_send = true; //manda mais um dado setando o chute para 0 (bug no código arduino do robô)
        }

        if (axis_send) calculateVelocity();
        else {
            linear_velocity_x_ = 0.0;
            linear_velocity_y_ = 0.0;
        }

        if (abs(axis_[AXIS_X]) < min_axis_) axis_[AXIS_X] = 0;
        if (abs(axis_[AXIS_Y]) < min_axis_) axis_[AXIS_Y] = 0;

        if (axis_send || rotating_ || button_send || dribbling_ || kicking_) {
            message_.setVelocityX((uint8_t)linear_velocity_x_);
            message_.setVelocityY((uint8_t)linear_velocity_y_);
            message_.setVelocityTheta((uint8_t)angular_velocity_);
            message_.setDirectionX(direction_x_);
            message_.setDirectionY(direction_y_);
            message_.setDirectionTheta(direction_theta_);

            cout << "Mensagem: " << endl;
            cout << message_ << endl;
            serial_->send(message_);
        }

        if(kicking_) ++kicking_;
    }

    message_.clear();
}

//Métodos do controle
bool ManualControl::readEventButton() {
    switch (event_.number) {
        case A: //Passe baixo
            if (event_.value) {
                message_.setKick(pass_power_);
                kicking_ = 1;
            }
            break;
        case X: //Chute baixo
            if (event_.value) {
                message_.setKick(kick_power_);
                kicking_ = 1;
            }
            break;
        case Y: //Lançamento
            if (event_.value) {
                message_.setKick(kick_power_);
                kicking_ = 1;
            }
            break;
        case LB: //Dribbler
            if (event_.value) message_.setDribbler(dribbler_velocity_);
            else message_.setDribbler(0);
            dribbling_ = event_.value;
            //drible h
            break;
        case RB:
            if (event_.value) bonus_linear_velocity_ =  1.0;
            else bonus_linear_velocity_ = 0;
            //boost
            break;
        case LT:
            if (event_.value) angular_velocity_ = max_angular_velocity_;
            else angular_velocity_ = 0.0;
            rotating_ = event_.value;
            direction_theta_ = 3;
            //gira h
            break;
        case RT:
            if(event_.value) angular_velocity_ = max_angular_velocity_;
            else angular_velocity_ = 0.0;
            rotating_ = event_.value;
            direction_theta_ = 1;
            //gira a-h
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

    linear_velocity_x_ = (int)(abs(axis_[AXIS_X]) * (max_linear_velocity_ + bonus_linear_velocity_) / max_axis_);
    linear_velocity_y_ = (int)(abs(axis_[AXIS_X]) * (max_linear_velocity_ + bonus_linear_velocity_) / max_axis_);
}