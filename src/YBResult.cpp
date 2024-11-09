// YBResult.cpp
#include "YBResult.h"
#include <Poco/Data/RecordSet.h>

using namespace Poco::Data;

// Define the Impl struct here in the source file
struct YBResult::Impl {
    std::unique_ptr<RecordSet> recordSet;
    size_t currentRow{0};
};

YBResult::YBResult() : pImpl(std::make_unique<Impl>()) {}

YBResult::~YBResult() = default;

bool YBResult::next() {
    if (!pImpl->recordSet) {
        return false;
    }

    if (pImpl->currentRow < pImpl->recordSet->rowCount()) {
        pImpl->currentRow++;
        return true;
    }
    return false;
}

Poco::Dynamic::Var YBResult::getValue(const std::string& columnName) const {
    if (!pImpl->recordSet) {
        throw YBError("No active result set");
    }

    try {
        return pImpl->recordSet->value(columnName, pImpl->currentRow - 1);
    }
    catch (const std::exception& e) {
        throw YBError(std::string("Failed to get value: ") + e.what());
    }
}

Poco::Dynamic::Var YBResult::getValue(size_t columnIndex) const {
    if (!pImpl->recordSet) {
        throw YBError("No active result set");
    }

    try {
        return pImpl->recordSet->value(columnIndex, pImpl->currentRow - 1);
    }
    catch (const std::exception& e) {
        throw YBError(std::string("Failed to get value: ") + e.what());
    }
}

std::vector<std::string> YBResult::getColumnNames() const {
    if (!pImpl->recordSet) {
        throw YBError("No active result set");
    }

    std::vector<std::string> columnNames;
    for (size_t i = 0; i < pImpl->recordSet->columnCount(); ++i) {
        columnNames.push_back(pImpl->recordSet->columnName(i));
    }
    return columnNames;
}

size_t YBResult::getColumnCount() const {
    return pImpl->recordSet ? pImpl->recordSet->columnCount() : 0;
}

size_t YBResult::getRowCount() const {
    return pImpl->recordSet ? pImpl->recordSet->rowCount() : 0;
}

void YBResult::setRecordSet(std::unique_ptr<Poco::Data::RecordSet> rs) {
    pImpl->recordSet = std::move(rs);
}
