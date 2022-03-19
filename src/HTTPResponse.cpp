/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPResponse.hpp"

using namespace std;

namespace Ishiko
{

HTTPResponse::HTTPResponse(HTTPStatusCode statusCode)
    : m_statusCode(statusCode)
{
}

HTTPResponse HTTPResponse::OK()
{
    return HTTPResponse(HTTPStatusCode::ok);
}

HTTPResponse HTTPResponse::MovedPermanently()
{
    return HTTPResponse(HTTPStatusCode::movedPermanently);
}

HTTPResponse HTTPResponse::BadRequest()
{
    return HTTPResponse(HTTPStatusCode::badRequest);
}

HTTPResponse HTTPResponse::NotFound()
{
    return HTTPResponse(HTTPStatusCode::notFound);
}

HTTPResponse HTTPResponse::InternalServerError()
{
    return HTTPResponse(HTTPStatusCode::internalServerError);
}

HTTPStatusCode HTTPResponse::statusCode() const
{
    return m_statusCode;
}

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
