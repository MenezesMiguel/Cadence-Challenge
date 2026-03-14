#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "utils.h"

std::chrono::system_clock::time_point Utils::readTimestamp() {
    std::string input;

    std::cout << "Enter time (YYYY-MM-DD HH:MM:SS): ";
    std::getline(std::cin, input);

    std::tm tm = {};
    std::istringstream ss(input);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

    std::time_t time = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(time);
}

std::string Utils::randomLetters(int quantity){
    std::string result(quantity, ' ');

    for (char& c : result) {
        c = 'A' + rand() % 26;
    }
    return result;
}

std::string Utils::plateGenerator(int sort){
    std::string plate;

    if(sort == 0){
        plate = randomLetters(3) + std::to_string(rand() % 9000 + 1000);
    } else {
        plate = randomLetters(3) +
                std::string(1, '0' + rand() % 10) +
                randomLetters(1) +
                std::to_string(rand() % 90 + 10);
    }

    return plate;
}