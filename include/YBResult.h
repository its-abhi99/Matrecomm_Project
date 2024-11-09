// YBResult.h
#pragma once

#include <memory>
#include <Poco/Data/RecordSet.h>
#include <Poco/Dynamic/Var.h>
#include "YBError.h"

class YBResult {
public:
    YBResult();
    ~YBResult();

    bool next();
    Poco::Dynamic::Var getValue(const std::string& columnName) const;
    Poco::Dynamic::Var getValue(size_t columnIndex) const;
    std::vector<std::string> getColumnNames() const;
    size_t getColumnCount() const;
    size_t getRowCount() const;

    void setRecordSet(std::unique_ptr<Poco::Data::RecordSet> rs);

private:
    // Forward declaration of Impl structure
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};