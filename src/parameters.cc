// Copyright 2019 FURGBot

#include "parameters.h"

#include <fstream>

namespace furgbol {
namespace parameters {

Parameters::Parameters() {
    read_parameters();

    std::cout << "****Parameters Setted****" << std::endl;
    std::cout << "-> Networking:" << std::endl;
    std::cout << "Serial Port: " << serial_port << std::endl;
    std::cout << "Frequency: " << frequency << std::endl;
    std::cout << "-> Limiting:" << std::endl;
    std::cout << "Min Axis: " << min_axis << std::endl;
    std::cout << "Max Axis: " << max_axis << std::endl;
    std::cout << "Max Linear Velocity: " << max_linear_velocity << std::endl;
    std::cout << "Max Angular Velocity: " << max_angular_velocity << std::endl;
    std::cout << "Dribbler Velocity: " << dribbler_velocity << std::endl;
    std::cout << "Kick Times: " << kick_times << std::endl;
    std::cout << "Kick Power: " << kick_power << std::endl;
    std::cout << "Pass Power: " << pass_power << std::endl;
    std::cout << "-> Robot ID: " << robot_id << std::endl;
    std::cout << std::endl;
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
    dribbler_velocity = j["limiting"]["velocities"]["dribbler"];
    kick_power = j["limiting"]["kick"]["power"];
    kick_times = j["limiting"]["kick"]["times"];
    pass_power = j["limiting"]["kick"]["pass"];

    robot_id = j["robot"]["id"];
    
    serial_port = j["networking"]["serial_port"];
    frequency = j["networking"]["frequency"];
}

}
}