// filepath: /micromouse-simulation/micromouse-simulation/src/utils/logger.cpp

#include "logger.h"
#include <fstream>
#include <iostream>
#include <string>

// Logger class implementation for handling simulation data logging
Logger::Logger(const std::string& logFilePath) : logFilePath(logFilePath) {}

// Method to log data to the specified log file
void Logger::logData(const std::string& data) {
    std::ofstream logFile;
    logFile.open(logFilePath, std::ios::app); // Open file in append mode
    if (logFile.is_open()) {
        logFile << data << std::endl; // Write data to log file
        logFile.close(); // Close the file
    } else {
        std::cerr << "Unable to open log file: " << logFilePath << std::endl;
    }
}

// Method to read logs from the log file
void Logger::readLog() const {
    std::ifstream logFile(logFilePath);
    if (logFile.is_open()) {
        std::string line;
        while (std::getline(logFile, line)) {
            std::cout << line << std::endl; // Output each line to console
        }
        logFile.close(); // Close the file
    } else {
        std::cerr << "Unable to open log file: " << logFilePath << std::endl;
    }
}