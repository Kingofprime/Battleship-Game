#include "logger.h"

// Records all the outputs and store it to an .txt file which can be accessed after the game
Logger::Logger(const std::string& file_name) : file(file_name, std::ios::out) {
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << file_name << " for writing." << std::endl;
        exit(1);
    }
}

Logger::~Logger() {
    if (file.is_open()) {
        file.close();
    }
}
