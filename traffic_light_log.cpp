#include <iostream>
#include <iomanip>
#include "traffic_light_log.h"

TrafficLightLog::TrafficLightLog() {}


std::vector<Register> TrafficLightLog::getLogsByTime(
    std::chrono::system_clock::time_point begin,
    std::chrono::system_clock::time_point finish
) {
    auto start = std::lower_bound(
        registers_.begin(),
        registers_.end(),
        begin,
        [](const Register& r, const auto& time) {
            return r.timestamp < time;
        }
    );

    auto end = std::upper_bound(
        registers_.begin(),
        registers_.end(),
        finish,
        [](const auto& time, const Register& r) {
            return time < r.timestamp;
        }
    );

    return std::vector<Register>(start, end);
}

void TrafficLightLog::addRegister(const Register& reg) {
    Register r = reg;
    // Linha original
    // r.timestamp = std::chrono::system_clock::now();

    // Linha para gerar massa de dados
    r.timestamp = reg.timestamp;
    registers_.push_back(r);
}

void TrafficLightLog::printAllLog() const {
    printFilteredLog(registers_);
}

void TrafficLightLog::printFilteredLog(const std::vector<Register>& logs) const {
    for (const auto& r : logs) {

        std::cout << r.license_plate << " ";

        std::time_t t = std::chrono::system_clock::to_time_t(r.timestamp);
        std::tm tm{};
        localtime_r(&t, &tm);
        std::cout << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << " ";

        switch (r.traffic_light_color) {
            case TrafficLightColor::RED:
                std::cout << "RED";
                break;
            case TrafficLightColor::YELLOW:
                std::cout << "YELLOW";
                break;
            case TrafficLightColor::GREEN:
                std::cout << "GREEN";
                break;
        }

        std::cout << std::endl;
    }
}