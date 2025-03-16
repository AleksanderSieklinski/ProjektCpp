#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>

/**
 * @class Logger
 * @brief A class to handle logging of simulation data.
 * 
 * This class provides functionality to log data to a file and read the log file.
 * 
 * @tparam T The type of data to be logged.
 */
template <typename T>
class Logger {
public:
    /**
     * @brief Constructs a Logger object.
     * 
     * This constructor initializes the Logger with the specified log file path.
     * It removes any existing log file and opens a new log file for appending data.
     * 
     * @param logFilePath The path to the log file.
     */
    Logger(const std::string& logFilePath);

    /**
     * @brief Logs data to the log file.
     * 
     * This function writes the specified data to the log file.
     * 
     * @param data The data to be logged.
     */
    void logData(const T& data);

    /**
     * @brief Reads and prints the log file.
     * 
     * This function reads the log file and prints its contents to the standard output.
     */
    void readLog() const;

private:
    std::string logFilePath; ///< The path to the log file.
    std::ofstream logFile; ///< The output file stream for the log file.
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