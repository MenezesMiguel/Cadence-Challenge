#ifndef TRAFFIC_LIGHT_LOG_H
#define TRAFFIC_LIGHT_LOG_H

#include <string>
#include <chrono>
#include <vector>


enum class TrafficLightColor {
    RED,
    YELLOW,
    GREEN
};

struct Register {
    std::string license_plate;
    std::chrono::system_clock::time_point timestamp;
    TrafficLightColor traffic_light_color;      
};

class TrafficLightLog {
    public:
    TrafficLightLog();

    void addRegister(const Register& reg);

    void printAllLog() const;
    void printFilteredLog(const std::vector<Register>& logs) const;

    std::vector<Register> getLogsByTime(
        std::chrono::system_clock::time_point begin,
        std::chrono::system_clock::time_point finish
    );

    private:
    std::vector<Register> registers_; 
};

#endif