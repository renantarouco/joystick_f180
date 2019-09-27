// Copyright 2019 FURGBot
#include "system.h"

int main() {
    std::shared_ptr<furgbol::System> system = furgbol::System::instance();
    system->init();
}