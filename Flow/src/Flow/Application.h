#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
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