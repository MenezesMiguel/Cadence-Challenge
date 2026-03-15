#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "traffic_light_log.h"
#include "utils.h"

static void simulateRegisters(TrafficLightLog& trafficLog, const Utils& utils);

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    TrafficLightLog trafficLog;
    Utils utils;
    simulateRegisters(trafficLog, utils);

    std::chrono::system_clock::time_point begin, end;

    while(true) {
        std::cout << "Insert initial date and hour (YYYY-MM-DD HH:MM:SS)" << std::endl;
        begin = utils.readTimestamp();

        std::cout << "Insert final date and hour (YYYY-MM-DD HH:MM:SS)" << std::endl;
        end = utils.readTimestamp();

        if(begin > end){
            std::cout << "Initial date has to be before than final date." << std::endl;
        } else {
            break;
        }
    }

    auto logs = trafficLog.getLogsByTime(begin, end);

    std::cout << "All registers:\n";
    trafficLog.printAllLog();

    std::cout << "\nFiltered licenses (" << logs.size() << "):\n";
    trafficLog.printFilteredLog(logs);

    return 0;
}


/**
 * @brief Simulates and generates 100 random traffic light registers
 * 
 * Creates 100 test registers with random license plates, traffic light colors,
 * and incrementing timestamps. Each register is automatically added to the
 * global trafficLog. Timestamps increase sequentially to maintain chronological
 * order in the log.
 * 
 * @return void (no return value)
 * 
 */

static void simulateRegisters(TrafficLightLog& trafficLog, const Utils& utils) {
    auto current_time = std::chrono::system_clock::now();

    for (int i = 0; i < 100; i++) {
        Register r;
        r.license_plate = utils.plateGenerator(std::rand() % 2);
        r.traffic_light_color = static_cast<TrafficLightColor>(std::rand() % 3);
        current_time += std::chrono::seconds(std::rand() % 5 + 10000);
        r.timestamp = current_time;

        trafficLog.addRegister(r);
    }
}

