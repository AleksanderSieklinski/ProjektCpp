#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>

/**
 * @class Logger
 * @brief A class to handle logging of simulation data.
 */
template <typename T>
class Logger {
public:
    Logger(const std::string& logFilePath);

    void logData(const T& data);

    void readLog() const;

private:
    std::string logFilePath;
    std::ofstream logFile;
};

template <typename T>
Logger<T>::Logger(const std::string& logFilePath) : logFilePath(logFilePath) {
    std::remove(logFilePath.c_str());
    logFile.open(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Unable to open log file: " << logFilePath << " - " << std::strerror(errno) << std::endl;
    }
}

template <typename T>
void Logger<T>::logData(const T& data) {
    if (logFile.is_open()) {
        logFile << data << std::endl;
    } else {
        std::cerr << "Log file is not open: " << logFilePath << std::endl;
    }
}

template <typename T>
void Logger<T>::readLog() const {
    std::ifstream logFile(logFilePath);
    if (logFile.is_open()) {
        std::string line;
        while (std::getline(logFile, line)) {
            std::cout << line << std::endl;
        }
        logFile.close();
    } else {
        std::cerr << "Unable to open log file: " << logFilePath << " - " << std::strerror(errno) << std::endl;
    }
}

#endif // LOGGER_H