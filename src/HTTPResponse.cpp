// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "HTTPResponse.hpp"

using namespace Ishiko;

HTTPResponse::ParserCallbacks::ParserCallbacks(HTTPResponse& response)
    : m_response(response)
{
}

void HTTPResponse::ParserCallbacks::onStatusCode(boost::string_view data)
{
    // TODO: handle error
    Error error;
    HTTPStatusCode statusCode(data.to_string(), error); // TODO: avoid to_string
    m_response.setStatusCode(statusCode);
}

void HTTPResponse::ParserCallbacks::onReasonPhrase(boost::string_view data)
{
    // TODO: do I store this only if it is different from the default?
}

void HTTPResponse::ParserCallbacks::onHeader(boost::string_view name, boost::string_view value)
{
    m_response.appendHeader(name.to_string(), value.to_string());   // TODO: avoid to_string.
}

void HTTPResponse::ParserCallbacks::onBodyFragment(boost::string_view data)
{
    // TODO: need to append to the body
    m_response.setBody(data.to_string());
}

HTTPResponse::HTTPResponse(HTTPStatusCode statusCode)
    : m_statusCode(statusCode)
{
}

HTTPResponse HTTPResponse::OK()
{
    HTTPResponse result(HTTPStatusCode::ok);
    result.setDateHeader(UTCTime::Now());
    return result;
}

HTTPResponse HTTPResponse::MovedPermanently(const URL& newLocation)
{
    HTTPResponse result(HTTPStatusCode::movedPermanently);
    result.setDateHeader(UTCTime::Now());
    result.setLocation(newLocation);
    return result;
}

HTTPResponse HTTPResponse::BadRequest()
{
    HTTPResponse result(HTTPStatusCode::badRequest);
    result.setDateHeader(UTCTime::Now());
    return result;
}

HTTPResponse HTTPResponse::NotFound()
{
    HTTPResponse result(HTTPStatusCode::notFound);
    result.setDateHeader(UTCTime::Now());
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

const HTTPHeaders& HTTPResponse::headers() const
{
    return m_headers;
}

void HTTPResponse::setStatusCode(HTTPStatusCode statusCode)
{
    m_statusCode = statusCode;
}

void HTTPResponse::appendHeader(const std::string& name, const std::string& value)
{
    m_headers.pushBack(name, value);
}

void HTTPResponse::setDateHeader(const UTCTime& time)
{
    // TODO: check if need to replace an existing header
    m_headers.pushBack(HTTPHeader::Date(time));
}

void HTTPResponse::setLocation(const URL& newLocation)
{
    // TODO: check if need to replace an existing header
    m_headers.pushBack(HTTPHeader::Location(newLocation));
}

void HTTPResponse::setBody(const std::string& body)
{
    m_body = body;
}

std::string HTTPResponse::toString() const
{
    std::string result;

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

    result.append("\r\n\r\n");
    result.append(m_body);

    return result;
}
