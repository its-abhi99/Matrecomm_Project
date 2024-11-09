//YBAuthentication.cpp

#include "YBAuthentication.h"
#include "YBError.h"
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>

struct YBAuthentication::Impl {
    std::string authToken;
};

YBAuthentication::YBAuthentication() 
    : pImpl(std::make_unique<Impl>()) {}

YBAuthentication::~YBAuthentication() = default;

bool YBAuthentication::authenticate(const std::string& username, 
                                     const std::string& password,
                                     const std::string& host) {
    try {
        Poco::Net::HTTPClientSession session(host, 5433); // Assuming the default YugaByte port
        
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, "/yugabyte/api/v1/login");
        request.setContentType("application/json");
        
        std::stringstream body;
        body << "{\"username\":\"" << username << "\",\"password\":\"" << password << "\"}";
        
        request.setContentLength(body.str().length());
        std::ostream& requestStream = session.sendRequest(request);
        requestStream << body.str();
        
        Poco::Net::HTTPResponse response;
        std::istream& responseStream = session.receiveResponse(response);
        
        if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK) {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(responseStream);
            Poco::JSON::Object::Ptr jsonObject = result.extract<Poco::JSON::Object::Ptr>();
            
            pImpl->authToken = jsonObject->getValue<std::string>("authToken");
            return true;
        } else {
            YBError::throw_error("Authentication failed: " + std::to_string(response.getStatus()) + " - " + response.getReason());
            return false;
        }
    } catch (const Poco::Exception& e) {
        YBError::throw_error("Authentication error: " + e.displayText());
        return false;
    }
}