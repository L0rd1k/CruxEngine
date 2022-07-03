#pragma once

namespace crux {

/** @brief Timestep value. **/
class Timestep {
public:
    /** @brief Constructor.
     * @param[in] time Timestep value. **/
    Timestep(float time = 0.0f)
        : _time(time) {}

    /** @brief Float type conversion overload. **/
    operator float() const {
        return _time;
    }

    /** @brief Get current timestep in seconds.
     * @return Decimal time value. **/
    const float getMilliseconds() const {
        return _time * 1000;
    }

    /** @brief Get current timestep in seconds.
     * @return Decimal time value. **/
    const float getSecond() const {
        return _time;
    }
private:
    float _time;  //> Current time value.
};

}  // namespace crux