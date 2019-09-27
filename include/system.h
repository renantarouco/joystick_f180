#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>

#include <lua.hpp>
#include <furgbol-core/io/serial_sender.h>

namespace furgbol {
  class System {
  public:
    struct SerialConfig {
      static std::string serial_port;
    };
    struct JoystickConfig {
      static uint8_t msg_type_;
      static int robot_id_;
      static int max_linear_velocity_; 
      static int max_angular_velocity_;
      static int dribbler_velocity_;
      static int kick_power_;
      static int pass_power_;
      static int max_axis_;
      static int min_axis_; 
      static int kick_times_;
      static std::chrono::duration<float> frequency_;
    };
    static std::shared_ptr<System> instance();
    void init();
    void exec();
  private:
    static std::shared_ptr<System> instance_;
    lua_State* l_;
  };
namespace lua_kernel {
  void load_kernel(lua_State*);
  int serial(lua_State*);
  int joystick(lua_State*);
} // namespace lua_kernel
} // namespace furgbol

#endif