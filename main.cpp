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

    std::cout << "Insira a data e hora inicial" << std::endl;
    auto begin = utils.readTimestamp();

    std::cout << "Insira a data e hora inicial" << std::endl;
    auto end = utils.readTimestamp();

    auto logs = trafficLog.getLogsByTime(begin, end);

    std::cout << "Registers added successfully." << std::endl;
    trafficLog.printAllLog();

    std::cout << "Placas Filtradas";

    trafficLog.printFilteredLog(logs);
    return 0;
}

void simulateRegisters(){

    auto current_time = std::chrono::system_clock::now();

    for(int i = 0; i<100; i++){
        Register r;
        r.license_plate = utils.plateGenerator(rand() % 2);
        r.traffic_light_color = static_cast<TrafficLightColor>(rand() % 3);
        current_time += std::chrono::seconds(rand() % 5 + 10000); // sempre aumenta
        r.timestamp = current_time;

        trafficLog.addRegister(r);
    };
};

