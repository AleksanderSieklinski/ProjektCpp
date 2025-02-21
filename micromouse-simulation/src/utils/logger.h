// filepath: /micromouse-simulation/micromouse-simulation/src/utils/logger.h

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>

/**
 * @class Logger
 * @brief A class to handle logging of simulation data.
 */
class Logger {
public:
    /**
     * @brief Constructor that initializes the logger with a specified log file path.
     * @param logFilePath The path to the log file.
     */
    Logger(const std::string& logFilePath);

    /**
     * @brief Logs data to the log file.
     * @param data The data to log.
     */
    void logData(const std::string& data);

    /**
     * @brief Reads the log file and outputs its contents.
     */
    void readLog() const;

private:
    std::string logFilePath; ///< The path to the log file.
    std::ofstream logFile;   ///< Output file stream for logging.
};

#endif // LOGGER_H