/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPRequest.hpp"

using namespace std;

namespace Ishiko
{

HTTPRequest::HTTPRequest(HTTPMethod method, URL requestURI)
    : m_method(method), m_requestURI(requestURI)
{
}

HTTPMethod HTTPRequest::method() const
{
    return m_method;
}

const URL& HTTPRequest::requestURI() const
{
    return m_requestURI;
}

void HTTPRequest::setConnectionHeader(HTTPHeader::ConnectionMode mode)
{
    // TODO: check if no previous header
    m_headers.push_back(HTTPHeader::Connection(mode));
}

string HTTPRequest::toString() const
{
    string result;

    result.append(m_method.toString());
    result.append(" ");
    string path = m_requestURI.path();
    if (path.empty())
    {
        path.append("/");
    }
    result.append(path); // TODO: query
    result.append(" HTTP/1.1\r\nHost: "); // TODO: other versions
    result.append(m_requestURI.host().value()); // TODO: what if no host
    result.append("\r\n");
    for (const HTTPHeader& header : m_headers)
    {
        result.append(header.toString());
        result.append("\r\n");
    }
    result.append("\r\n");

    return result;
}

}
