//YBError.cpp
#include "YBError.h"

YBError::YBError(const std::string& message)
    : std::runtime_error(message) {}

YBError::YBError(const char* message)
    : std::runtime_error(message) {}

void YBError::throw_error(const std::string& message) {
    throw YBError(message);
}