/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPRequest.hpp"

using namespace Ishiko;

HTTPRequest::HTTPRequest(HTTPMethod method, URL requestURI)
    : m_method(method), m_requestURI(requestURI)
{
    if (m_requestURI.host())
    {
        setHostHeader(m_requestURI.host().value());
    }
}

HTTPMethod HTTPRequest::method() const
{
    return m_method;
}

const URL& HTTPRequest::requestURI() const
{
    return m_requestURI;
}

const HTTPHeaders& HTTPRequest::headers() const
{
    return m_headers;
}

void HTTPRequest::setConnectionHeader(HTTPHeader::ConnectionMode mode)
{
    m_headers.set(HTTPHeader::Connection(mode));
}

void HTTPRequest::setHostHeader(const std::string& host)
{
    m_headers.set(HTTPHeader::Host(host));
}

std::string HTTPRequest::toString() const
{
    std::string result;

    result.append(m_method.toString());
    result.append(" ");
    std::string path = m_requestURI.path();
    if (path.empty())
    {
        path.append("/");
    }
    result.append(path); // TODO: query
    result.append(" HTTP/1.1\r\n"); // TODO: other versions
    for (const HTTPHeader& header : m_headers)
    {
        result.append(header.toString());
        result.append("\r\n");
    }
    result.append("\r\n");

    return result;
}
