#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string& file_name);
    ~Logger();

    template<typename T>
    void log(const T& message);

    template<typename T>
    Logger& operator<<(const T& message);

private:
    std::ofstream file;
};

#include "logger.tpp"

#endif // LOGGER_H


