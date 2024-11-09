//YBconnection.h
#pragma once

#include <string>
#include <memory>
#include <Poco/Data/SessionPool.h>

class YBConnection {
public:
    YBConnection();
    ~YBConnection();

    bool connect(const std::string& host, const std::string& port, const std::string& database,
                 const std::string& username, const std::string& password);
    bool disconnect();
    bool isConnected() const;
    std::shared_ptr<Poco::Data::SessionPool> getSessionPool() const;

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};