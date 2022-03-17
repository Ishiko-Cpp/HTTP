/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPRESPONSE_HPP_
#define _ISHIKO_CPP_HTTP_HTTPRESPONSE_HPP_

#include "HTTPStatusCode.hpp"
#include "HTTPVersion.hpp"
#include <string>

namespace Ishiko
{

class HTTPResponse
{
public:
    void setBody(const std::string& body);

    // TODO: this is a naive way to create a response as it could be very large. Some form of streaming, especially of
    // the body is required but it'll do for now
    std::string toString() const;

private:
    HTTPVersion m_version;
    HTTPStatusCode m_statusCode;
    std::string m_body;
};

}

#endif
