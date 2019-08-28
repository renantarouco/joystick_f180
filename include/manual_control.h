// Copyright 2019 FURGBot

#ifndef MANUAL_CONTROL_H
#define MANUAL_CONTROL_H

#include "serial_message.h"
#include "serial_sender.h"
#include "parameters.h"

#include "joystick.hh"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdio>
#include <chrono>

using namespace std;
using namespace furgbol::joystick;
using namespace furgbol::parameters;
using namespace std::chrono;

enum Axis{
    AXIS_X, AXIS_Y
};

enum Buttons {
    A = 0, X = 2, LB = 4, LS = 11, RS = 12
};

/*!
 * \brief A classe ManualControl administra uma thread para fazer leitura do joystick, montagem do pacote serial
 * e adição na lista para envio da thread SerialCommunicator
 */
class ManualControl {
    private:
        //Variáveis de thread
        bool running_; //!<Flag de controle de execução da Thread
        thread td_; //!<Thread da classe
        mutex mu_; //!<Mutex para escrita na flag running

        //Variáveis do joystick
        int device_number_; //!<Número do joystick utilizado pela thread
        Joystick *joystick_; //!<Objeto da classe Joystick para fazer leitura do arquivo em que o joystick escreve seus dados
        JoystickEvent event_; //!<Objeto da classe JoystickEvent para verificar se houve algum evento no joystick que deve ser processado
        vector<short> axis_; //!<Vetor que guarda o valor dos analógicos do joystick

        //Variáveis de controle
        int robot_id_; //!<Variável que guarda o id do robô que vai ser controlado
        bool rotating_; //!<Flag para indicar se o botão de rotação está pressionado ou não
        bool dribbling_; //!<Flag para indicar se o botão de dribbler está pressionado ou não
        int kicking_; //!<Variável para garantir que o robô vai tentar chutar kick_times_ para facilitar o chute na hora de controlar
        int linear_velocity_x_; //!<Variável que guarda a velocidade linear em x
        int linear_velocity_y_; //!<Variável que guarda a velocidade linear em y
        int angular_velocity_; //!<Variável que guarda a velocidade angular
        int direction_x_; //!<Variável que guarda a direção da velocidade linear em x
        int direction_y_; //!<Variável que guarda a direção da velocidade linear em y
        int direction_theta_; //!<Variável que guarda a direção da velocidade angular

        //Parâmetros
        int max_linear_velocity_; //!<Velocidade linear máxima que o robô pode assumir
        int max_angular_velocity_; //!<Velocidade angular máxima que o robô pode assumir
        int dribbler_velocity_; //!<Velocidade do dribbler pwm
        int kick_power_; //!<Força do chute em pwm
        int pass_power_; //!<Força do passe em pwm
        int max_axis_; //!<Variável para armazenar o valor máximo lido pelo axis
        int min_axis_; //!<Variável para armazenar o valor mínimo lido pelo axis
        int kick_times_; //!<Variável para armazenar o número de vezes que o robô vai tentar chutar
        duration<float> frequency_; //!<Variável para armazenar a frequência de transmissão

        //Networking
        SerialMessage message_; //!<Mensagem que será envidada
        SerialSender *serial_; //!<Ponteiro para a thread de comunicação serial

        /*!
        * \brief calculateVelocity calcula a velocidade linear do robô com base no valor oferecido pelo vetor axis
        */
        void calculateVelocity();

        /*!
        * \brief readEventButton processa um evento que seja disparado por um botão, verificando que tipo de ação se deve tomar
        * \return booleano indicando se há ou não a necessidade de enviar um dado para o robô
        */
        bool readEventButton();

        /*!
        * \brief readEventAxis processa um evento que seja disparado por um analógico, preenchendo o vetor axis
        */
        void readEventAxis();

        /*!
        * \brief verifyVelocityAxis verifica se os valores que estão no vetor de axis são suficientes para calcular a velocidade
        * \return booleano indicando se o dado é ou não relevante
        */
        bool verifyVelocityAxis();

        /*!
        * \brief run é o loop principal a thread, passado por parâmetro para td
        */
        void run();

    public:
        ManualControl();
        ManualControl(int device_number, Parameters param, SerialSender *serial);

        ~ManualControl();

        /*!
        * \brief start modifica a flag running para true e reconstroi a thread td para reiniciar a thread
        */
        void start();
        /*!
        * \brief stop trava com o mutex, modificia a flag running para false e da join na thread td
        */
        void stop();
};

#endif // MANUAL_CONTROL_H