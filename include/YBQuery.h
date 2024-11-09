//YBQuery.h

#pragma once

#include <memory>
#include "YBConnection.h"
#include "YBResult.h"

class YBQuery {
public:
    // Constructor
    YBQuery(std::shared_ptr<YBConnection> connection);

    // Method to execute the query
    std::shared_ptr<YBResult> executeQuery(const std::string& query);

private:
    std::shared_ptr<YBConnection> _connection;  // Store the connection
};