#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <string>

class Utils {
public:
    static std::chrono::system_clock::time_point readTimestamp();
    std::string plateGenerator(int sort) const;
    std::string randomLetters(int quantity)const;
};

#endif