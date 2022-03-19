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
    HTTPResponse result(HTTPStatusCode::ok);
    result.setDateHeader(TimePoint::Now());
    return result;
}

HTTPResponse HTTPResponse::MovedPermanently(const URL& newLocation)
{
    HTTPResponse result(HTTPStatusCode::movedPermanently);
    result.setDateHeader(TimePoint::Now());
    result.setLocation(newLocation);
    return result;
}

HTTPResponse HTTPResponse::BadRequest()
{
    HTTPResponse result(HTTPStatusCode::badRequest);
    result.setDateHeader(TimePoint::Now());
    return result;
}

HTTPResponse HTTPResponse::NotFound()
{
    HTTPResponse result(HTTPStatusCode::notFound);
    result.setDateHeader(TimePoint::Now());
    return result;
}

HTTPResponse HTTPResponse::InternalServerError()
{
    return HTTPResponse(HTTPStatusCode::internalServerError);
}

HTTPStatusCode HTTPResponse::statusCode() const
{
    return m_statusCode;
}

void HTTPResponse::setDateHeader(const TimePoint& time)
{
    // TODO: check if need to replace an existing header
    m_headers.emplace_back(HTTPHeader::Date(time));
}

void HTTPResponse::setLocation(const URL& newLocation)
{
    // TODO: check if need to replace an existing header
    m_headers.emplace_back(HTTPHeader::Location(newLocation));
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

    for (const HTTPHeader& header : m_headers)
    {
        result.append(header.toString());
        result.append("\r\n");
    }

    result.append("Content-Length: ");
    result.append(to_string(m_body.size()));
    result.append("\r\n\r\n");
    result.append(m_body);

    return result;
}

}
