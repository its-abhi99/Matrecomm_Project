//YBConnection.cpp
#include "YBConnection.h"
#include "YBError.h"
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/PostgreSQL/Connector.h>

using namespace Poco::Data;

struct YBConnection::Impl {
    std::shared_ptr<SessionPool> sessionPool;
    bool connected{false};
};

YBConnection::YBConnection() : pImpl(std::make_unique<Impl>()) {
    PostgreSQL::Connector::registerConnector();
}

YBConnection::~YBConnection() {
    if (isConnected()) {
        disconnect();
    }
    PostgreSQL::Connector::unregisterConnector();
}

bool YBConnection::connect(const std::string& host, const std::string& port,
                           const std::string& database, const std::string& username,
                           const std::string& password) {
    try {
        std::string connString = "host=" + host + " port=" + port +
                                 " dbname=" + database + " user=" + username +
                                 " password=" + password;

        pImpl->sessionPool = std::make_shared<SessionPool>(
            "PostgreSQL", connString, 1, 20, 5);

        // Test connection
        Session session(pImpl->sessionPool->get());
        session << "SELECT 1;", Poco::Data::Keywords::now;

        pImpl->connected = true;
        return true;
    } catch (const std::exception& e) {
        throw YBError(std::string("Connection failed: ") + e.what());
    }
}

bool YBConnection::disconnect() {
    if (pImpl->sessionPool) {
        pImpl->sessionPool->shutdown();
        pImpl->connected = false;
        return true;
    }
    return false;
}

bool YBConnection::isConnected() const {
    return pImpl->connected;
}

std::shared_ptr<SessionPool> YBConnection::getSessionPool() const {
    return pImpl->sessionPool;
}
