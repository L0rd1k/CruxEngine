#pragma once

#include "Core.h"

#include <iostream>

namespace Flow {

class Application {
   public:
    Application();
    virtual ~Application();
    void Run();
};

Application* CreateApplication();

}  // namespace Flow