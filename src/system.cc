#include "system.h"

namespace furgbol {
  std::shared_ptr<System> System::instance_ = nullptr;
  std::string System::SerialConfig::serial_port = "";
  std::shared_ptr<System> System::instance() {
    if (instance_ == nullptr) {
      instance_ = std::make_shared<System>();
    }
    return instance_;
  }
  void System::init() {
    std::cout << "system init" << std::endl;
    lua_State* L = luaL_newstate();
    lua_kernel::load_kernel(L);
    int r = luaL_dofile(L, "../scripts/config.lua");
    if (r != 0) {
      std::cout << lua_tostring(L, -1) << std::endl;
    }
  }
}