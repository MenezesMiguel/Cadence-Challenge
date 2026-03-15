#include <iostream>
#include <iomanip>
#include "traffic_light_log.h"

TrafficLightLog::TrafficLightLog() {}

/**
 * @brief Get logs filtered between two dates
 * 
 * Uses binary search (lower_bound and upper_bound) to efficiently retrieve
 * 
 * @param begin Initial date/time to filter
 * @param finish Final date/time to filter
 * 
 * @return std::vector<Register> A vector containing all registers within the time range
 * 
 * @note Assumes the internal registers_ vector is sorted by timestamp
 * @note Time complexity: O(log n) for search + O(k) for copying, where k is the number of matches
 * @note Returns an empty vector if no registers are found in the range
 * 
 * @example
 * TrafficLightLog log;
 * // Assuming log has some registers...
 * 
 * auto beginTime = 2026-03-15 00:00:00;
 * auto endTime = 2026-03-15 23:59:59;
 * 
 * std::vector<Register> filtered = log.getLogsByTime(beginTime, endTime);
 * // Returns: All registers from March 15, 2026
 * 
 * for (const auto& reg : filtered) {
 *     std::cout << reg.license_plate << " - " << reg.traffic_light_color << std::endl;
 * }
 */
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

/**
 * @brief Add a new register to the log array
 * 
 * Appends a traffic light event register to the internal registers_ vector.
 * The timestamp can either be set to the current system time or use the
 * timestamp from the provided register (useful for data generation/testing).
 * 
 * @param reg The register to add to the log
 * 
 * @return void (no return value)
 * 
 * @note Currently uses the timestamp from the provided register (for data generation)
 * @note Original behavior (setting timestamp to current time) is commented out
 * @note Time complexity: O(1) amortized (vector push_back)
 * 
 * @example
 * TrafficLightLog log;
 * 
 * // Create a new register
 * Register reg;
 * reg.license_plate = "ABC1234";
 * reg.traffic_light_color = TrafficLightColor::RED;
 * reg.timestamp = std::chrono::system_clock::now();
 * 
 * // Add to log
 * log.addRegister(reg);
 */
void TrafficLightLog::addRegister(const Register& reg) {
    Register r = reg;
    // Original line - sets timestamp to current time
    // r.timestamp = std::chrono::system_clock::now();

    // Line for data generation - uses provided timestamp
    r.timestamp = reg.timestamp;
    registers_.push_back(r);
}

/**
 * @brief Print all logs to standard output
 * 
 * Displays all stored traffic light registers by calling printFilteredLog
 * with the complete registers_ vector.
 * 
 * @return void (no return value)
 * 
 * @see printFilteredLog()
 * 
 * @example
 * TrafficLightLog log;
 * 
 * // Print all logs
 * log.printAllLog();
 * 
 * // Output:
 * // ABC1234 15-03-2026 14:30:00 RED
 * // XYZ5678 15-03-2026 14:31:00 GREEN
 */
void TrafficLightLog::printAllLog() const {
    printFilteredLog(registers_);
}


/**
 * @brief Print a filtered list of registers
 * 
 * Displays each register in the format:
 * LICENSE_PLATE DD-MM-YYYY HH:MM:SS COLOR
 * 
 * @param logs Vector of registers to print
 * 
 * @note Uses thread-safe localtime_r for time conversion
 * 
 * @example
 * auto filtered = log.getLogsByTime(begin, end);
 * log.printFilteredLog(filtered);
 * 
 * // Output:
 * // ABC1234 15-03-2026 14:30:00 RED
 * // XYZ5678 15-03-2026 14:35:12 GREEN
 */
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