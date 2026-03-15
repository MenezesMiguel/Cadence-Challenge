#include <iostream>
#include "traffic_light_log.h"
#include "utils.h"

TrafficLightLog trafficLog;
Utils utils;
std::string randomLetters(int);
std::string plateGenerator(int);
void simulateRegisters();

int main() {

    srand(time(NULL));

    simulateRegisters();

    decltype(utils.readTimestamp()) begin, end;

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

auto logs = trafficLog.getLogsByTime(begin, end);  // Now this works!

    std::cout << "Registers added successfully." << std::endl;
    trafficLog.printAllLog();

    std::cout << "Filtered licences";
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
void simulateRegisters(){

    auto current_time = std::chrono::system_clock::now();

    for(int i = 0; i<100; i++){
        Register r;
        r.license_plate = utils.plateGenerator(rand() % 2);
        r.traffic_light_color = static_cast<TrafficLightColor>(rand() % 3);
        current_time += std::chrono::seconds(rand() % 5 + 10000); // Always increases
        r.timestamp = current_time;

        trafficLog.addRegister(r);
    };
};

