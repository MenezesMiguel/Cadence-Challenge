#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "utils.h"

/**
 * @brief Reads and validates a timestamp from user input
 * 
 * Validates:
 * - Format: YYYY-MM-DD HH:MM:SS
 * - Month: 1-12
 * - Day: 1-31 (respecting month length and leap years)
 * - Hour: 0-23
 * - Minute: 0-59
 * - Second: 0-59
 * 
 * @return std::chrono::system_clock::time_point The validated timestamp
 * 
 * @note This function will loop indefinitely until valid input is received
 * @note Leap years are automatically detected and validated
 * 
 * @example
 * Utils utils;
 * auto timestamp = utils.readTimestamp();
 * // User enters: 2026-03-15 14:30:00
 * // Returns: time_point representing March 15, 2026 at 2:30 PM
 */
std::chrono::system_clock::time_point Utils::readTimestamp() {
    while(true) {
        std::string input;
        std::cout << "Enter time (YYYY-MM-DD HH:MM:SS): ";
        std::getline(std::cin, input);

        int year, month, day, hour, minute, second;
        
        // Parse with sscanf
        if(sscanf(input.c_str(), "%d-%d-%d %d:%d:%d", 
                  &year, &month, &day, &hour, &minute, &second) != 6) {
            std::cout << "Invalid format! Use YYYY-MM-DD HH:MM:SS format" << std::endl;
            continue;
        }

        // Validate hour, minute, second
        if(hour < 0 || hour > 23) {
            std::cout << "Invalid hour! Must be between 0 and 23." << std::endl;
            continue;
        }
        if(minute < 0 || minute > 59) {
            std::cout << "Invalid minute! Must be between 0 and 59." << std::endl;
            continue;
        }
        if(second < 0 || second > 59) {
            std::cout << "Invalid second! Must be between 0 and 59." << std::endl;
            continue;
        }

        // Validate month
        if(month < 1 || month > 12) {
            std::cout << "Invalid month! Must be between 1 and 12." << std::endl;
            continue;
        }

        // Validate day
        if(day < 1 || day > 31) {
            std::cout << "Invalid day! Must be between 1 and 31." << std::endl;
            continue;
        }

        // Validate specific days per month
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Check leap year
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if(isLeap && month == 2) {
            daysInMonth[1] = 29;
        }
        
        if(day > daysInMonth[month - 1]) {
            std::cout << "Invalid day for month " << month << "! ";
            std::cout << "This month has only " << daysInMonth[month - 1] << " days." << std::endl;
            continue;
        }

        // Create std::tm
        std::tm tm = {};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        tm.tm_isdst = -1;

        std::time_t time = std::mktime(&tm);
        
        if(time == -1) {
            std::cout << "Error converting date/time!" << std::endl;
            continue;
        }

        return std::chrono::system_clock::from_time_t(time);
    }
}

/**
 * @brief Generate a random sequence of uppercase letters.
 * 
 * Creates a string containing random uppercase letters (A-Z).
 * 
 * @param quantity The number of random letters to generate
 * 
 * @return std::string The randomly generated string of letters
 * 
 * @warning Uses rand(), ensure srand() is called before using this function
 * 
 * @example
 * Utils utils;
 * std::string randomLettersSequence = utils.randomLetters(4);
 * // Returns: "DSJN" (or any random 4-letter combination)
 */

std::string Utils::randomLetters(int quantity){
    std::string result(quantity, ' ');

    for (char& c : result) {
        c = 'A' + rand() % 26;
    }
    return result;
}

/**
 * @brief Generates a random license plate string for a big data quantity
 * 
 * Generates a license plate in one of two formats based on the sort parameter:
 * - sort = 0: Old format (ABC1234) - 3 letters followed by 4 digits
 * - sort = 1: New format (ABC1D23) - 3 letters, 1 digit, 1 letter, 2 digits
 * 
 * @param sort The format type (0 for old format, 1 for new format)
 * 
 * @return std::string The generated license plate
 * 
 * @warning Uses rand(), ensure srand() is called before using this function
 * 
 * @example
 * Utils utils;
 * std::string oldPlate = utils.plateGenerator(0);
 * // Returns: "ABC1234" (3 letters + 4 digits)
 * 
 * std::string newPlate = utils.plateGenerator(1);
 * // Returns: "ABC1D23" (3 letters + 1 digit + 1 letter + 2 digits)
 */
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