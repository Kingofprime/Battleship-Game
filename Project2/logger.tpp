#ifndef LOGGER_TPP
#define LOGGER_TPP

template<typename T>
void Logger::log(const T& message) {
    std::cout << message;
    file << message;
}

template<typename T>
Logger& Logger::operator<<(const T& message) {
    log(message);
    return *this;
}

#endif // LOGGER_TPP
