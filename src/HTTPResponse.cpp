/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPResponse.hpp"

using namespace std;

namespace Ishiko
{

void HTTPResponse::setBody(const string& body)
{
    m_body = body;
}

string HTTPResponse::toString() const
{
    string result;

    result.append(m_version.toString());
    result.append(" ");
    result.append(m_statusCode.toString());
    result.append(" ");
    result.append(m_statusCode.getReasonPhrase());
    result.append("\r\n");
    result.append("Content-Length: ");
    result.append(to_string(m_body.size()));
    result.append("\r\n\r\n");
    result.append(m_body);

    return result;
}

}
