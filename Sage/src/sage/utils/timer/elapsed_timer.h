#pragma once

#include <chrono>

namespace sage {

class ElapsedTimer {
public:
    using clock = std::chrono::steady_clock;
    using second = std::chrono::duration<double, std::ratio<1>>;

public:
    ElapsedTimer()
        : _beg(clock::now()) {}
    void start() {
        restart();
    }
    void restart() {
        _beg = clock::now();
    }
    double elapsedSec() const {
        return std::chrono::duration_cast<second>(clock::now() - _beg).count();
    }
    int elapsedMs() const {
        return elapsedSec() * 1000;
    }
    bool expired(int milliseconds) {
        return elapsedMs() > milliseconds;
    }

private:
    std::chrono::time_point<clock> _beg;
};

}  // namespace sage