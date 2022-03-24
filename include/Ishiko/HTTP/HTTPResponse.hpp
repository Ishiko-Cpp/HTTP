/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPRESPONSE_HPP_
#define _ISHIKO_CPP_HTTP_HTTPRESPONSE_HPP_

#include "HTTPHeader.hpp"
#include "HTTPStatusCode.hpp"
#include "HTTPVersion.hpp"
#include <Ishiko/Time.hpp>
#include <Ishiko/Types.hpp>
#include <string>
#include <vector>

namespace Ishiko
{

class HTTPResponse
{
public:
    HTTPResponse(HTTPStatusCode statusCode);
    static HTTPResponse OK();
    static HTTPResponse MovedPermanently(const URL& newLocation);
    static HTTPResponse BadRequest();
    static HTTPResponse NotFound();
    static HTTPResponse InternalServerError();

    HTTPStatusCode statusCode() const;

    void setStatusCode(HTTPStatusCode statusCode);
    void setDateHeader(const UTCTime& time);
    void setLocation(const URL& newLocation);
    void setBody(const std::string& body);

    // TODO: this is a naive way to create a response as it could be very large. Some form of streaming, especially of
    // the body is required but it'll do for now
    std::string toString() const;

private:
    HTTPVersion m_version;
    HTTPStatusCode m_statusCode;
    std::vector<HTTPHeader> m_headers;
    std::string m_body;
};

}

#endif
