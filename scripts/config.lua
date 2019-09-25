function startConfiguration()
    newSerial({
        serial_port = "/dev/ttyUSB0"
    })

    newJoystick({
        communication_frequency = 100,
        message_type = 0,
        robot_id = 0,
        min_axis_value = 10000,
        max_axis_value = 32767,
        max_linear_velocity = 50,
        max_angular_velocity = 90,
        dribbler_velocity = 127,
        kick_power = 127,
        kick_times = 127,
        pass_power = 50
    })
end