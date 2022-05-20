/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPREQUEST_HPP_
#define _ISHIKO_CPP_HTTP_HTTPREQUEST_HPP_

#include "HTTPHeader.hpp"
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

    void setConnectionHeader(HTTPHeader::ConnectionMode mode);

    std::string toString() const;

private:
    HTTPMethod m_method;
    URL m_requestURI;
    std::vector<HTTPHeader> m_headers;
};

}

#endif
