/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPREQUEST_HPP_
#define _ISHIKO_CPP_HTTP_HTTPREQUEST_HPP_

#include "HTTPHeader.hpp"
#include "HTTPHeaders.hpp"
#include "HTTPMethod.hpp"
#include <Ishiko/Types.hpp>
#include <string>
#include <vector>

namespace Ishiko
{

class HTTPRequest
{
public:
    // TODO: what if the scheme of the uri is not http(s)
    HTTPRequest(HTTPMethod method, URL requestURI);

    HTTPMethod method() const;
    const URL& requestURI() const;
    const HTTPHeaders& headers() const;

    void setConnectionHeader(HTTPHeader::ConnectionMode mode);
    void setHostHeader(const std::string& host);

    std::string toString() const;

private:
    HTTPMethod m_method;
    URL m_requestURI;
    HTTPHeaders m_headers;
};

}

#endif
