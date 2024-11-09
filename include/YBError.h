//YBError.h
#ifndef YBERROR_H
#define YBERROR_H

#include <stdexcept>
#include <string>

class YBError : public std::runtime_error {
public:
    YBError(const std::string& message);
    YBError(const char* message);

    static void throw_error(const std::string& message);
};

#endif // YBERROR_H