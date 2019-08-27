// Copyright 2019 FURGBot

#include "parameters.h"

#include <fstream>

namespace furgbol {
namespace parameters {

Parameters::Parameters() {
    read_parameters();
}

Parameters::~Parameters() {}

void Parameters::read_parameters() {
    std::ifstream i("config/params.json");
    nlohmann::json j;
    i >> j;

    min_axis = j["limiting"]["axis"]["min"];
    max_axis = j["limiting"]["axis"]["max"];
    max_linear_velocity = j["limiting"]["velocities"]["max_linear"];
    max_angular_velocity = j["limiting"]["velocities"]["max_angular"];
    bonus_linear_velocity = j["limiting"]["velocities"]["bonus_linear"];
    dribbler_velocity = j["limiting"]["velocities"]["dribbler"];
    kick_power = j["limiting"]["kick"]["power"];
    kick_times = j["limiting"]["kick"]["times"];
    pass_power = j["limiting"]["kick"]["pass"];

    robot_id = j["robot"]["id"];
    
    serial_port = j["networking"]["serial_port"];
}

}
}