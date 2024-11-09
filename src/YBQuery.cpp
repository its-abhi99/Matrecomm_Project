//YBQuery.cpp
#include "YBQuery.h"
#include "YBResult.h"
#include "YBError.h"
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>
#include <Poco/Data/RecordSet.h>

YBQuery::YBQuery(std::shared_ptr<YBConnection> connection)
    : _connection(std::move(connection)) {}

std::shared_ptr<YBResult> YBQuery::executeQuery(const std::string& query) {
    try {
        // Corrected session retrieval from session pool
        Poco::Data::Session session = _connection->getSessionPool()->get();

        Poco::Data::Statement stmt(session);
        stmt << query, Poco::Data::Keywords::now;

        // Execute the query and get the result set
        Poco::Data::RecordSet rs(stmt);

        // Create YBResult and set the RecordSet using the setter
        std::shared_ptr<YBResult> result = std::make_shared<YBResult>();
        result->setRecordSet(std::make_unique<Poco::Data::RecordSet>(rs));

        return result;
    } catch (const std::exception& e) {
        throw YBError(std::string("Query execution failed: ") + e.what());
    }
}