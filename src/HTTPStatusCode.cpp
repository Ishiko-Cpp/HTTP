/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPStatusCode.hpp"
#include "HTTPErrorCategory.hpp"
#include <Ishiko/Text.hpp>

using namespace Ishiko;

HTTPStatusCode::HTTPStatusCode(Value value)
    : m_value(value)
{
}

HTTPStatusCode::HTTPStatusCode(unsigned short value)
    : m_value(value)
{
}

HTTPStatusCode::HTTPStatusCode(const std::string& value, Error& error)
{
    ASCII::Convert(value, m_value, error);
    if (!error)
    {
        // HTTP status code are three-digit integers
        if (m_value > 999)
        {
            // TODO : proper error message
            Fail(error, HTTPErrorCategory::Value::generic, "", __FILE__, __LINE__);
        }
    }
}

std::string HTTPStatusCode::getReasonPhrase() const
{
    switch (m_value)
    {
    case ok:
        return "OK";

    case movedPermanently:
        return "Moved Permanently";

    case badRequest:
        return "Bad Request";

    case notFound:
        return "Not Found";

    case internalServerError:
        return "Internal Server Error";

    default:
        // TODO
        return "";
    }
}

bool HTTPStatusCode::operator==(unsigned int value) const
{
    return (m_value == value);
}

bool HTTPStatusCode::operator!=(unsigned int value) const
{
    return (m_value != value);
}

std::string HTTPStatusCode::toString() const
{
    switch (m_value)
    {
    case ok:
        return "200";

    case movedPermanently:
        return "301";

    case badRequest:
        return "400";

    case notFound:
        return "404";

    case internalServerError:
        return "500";

    default:
        // TODO
        return "";
    }
}
