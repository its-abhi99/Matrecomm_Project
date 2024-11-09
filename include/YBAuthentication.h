//YBAuthentication.h
#pragma once

#include <string>
#include <memory>

class YBAuthentication {
public:
    YBAuthentication();
    ~YBAuthentication();

    bool authenticate(const std::string& username, const std::string& password, const std::string& host);
    std::string getAuthToken() const;

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};