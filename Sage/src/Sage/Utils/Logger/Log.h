#pragma once

#include <time.h>

#include <chrono>
#include <iostream>
#include <string>

namespace Sage {

class Log {
public:
    Log() {}
    virtual ~Log() {}

    Log& operator<<(const std::string str) {
        std::cout << str << " ";
        return *this;
    }

    static std::string getTime() {
        auto now = std::chrono::system_clock::now();
        time_t t = std::chrono::system_clock::to_time_t(now);
        std::string strTime = ctime(&t);
        return strTime.substr(0, strTime.length() - 1);
    }

    template <typename... Args>
    static void error(Args&&... args) {
        std::cout << "[" << getTime() << "] ";
        ((std::cout << "\033[1;31;49m" <<std::forward<Args>(args)), ...);
        std::cout << "\033[0m" << std::endl;
    }

    template <typename... Args>
    static void warning(Args&&... args) {
        std::cout << "[" << getTime() << "] ";
        ((std::cout << "\033[1;35;49m" << std::forward<Args>(args)), ...);
        std::cout << "\033[0m" << std::endl;
    }

    template <typename... Args>
    static void trace(Args&&... args) {
        std::cout << "[" << getTime() << "] ";
        ((std::cout << "\033[1;32;49m" << std::forward<Args>(args)), ...);
        std::cout << "\033[0m" << std::endl;
    }

    template <typename... Args>
    static void info(Args... args) {
        std::cout << "[" << getTime() << "] ";
        ((std::cout << "\033[0;34;49m" << std::forward<Args>(args)), ...);
        std::cout << "\033[0m" << std::endl;
    }

    template <typename... Args>
    static void debug(Args&&... args) {
        ((std::cout << std::forward<Args>(args)), ...);
        std::cout << std::endl;
    }

    template <typename... Args>
    static void critical(Args&&... args) {
        std::cout << "[" << getTime() << "] ";
        ((std::cout << "\033[1;31;49m" <<  std::forward<Args>(args)), ...);
        std::cout << "\033[0m" << std::endl;
    }
};

}  // namespace Sage