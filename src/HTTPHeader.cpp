// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "HTTPHeader.hpp"
#include <boost/date_time.hpp>

using namespace Ishiko;

HTTPHeader::HTTPHeader(std::string name, std::string value)
    : m_name(std::move(name)), m_value(std::move(value))
{
}

HTTPHeader HTTPHeader::Connection(ConnectionMode mode)
{
    switch (mode)
    {
    case ConnectionMode::close:
        return HTTPHeader("Connection", "close");

    case ConnectionMode::keep_alive:
        return HTTPHeader("Connection", "keep-alive");

    default:
        // TODO
        return HTTPHeader("Connection", "close");
    }
}

HTTPHeader HTTPHeader::ContentLength(size_t length)
{
    return HTTPHeader("Content-Length", std::to_string(length));
}

HTTPHeader HTTPHeader::Date(const UTCTime& time)
{
    return HTTPHeader("Date", time.toRFC7231String());
}

HTTPHeader HTTPHeader::Host(const std::string& host)
{
    return HTTPHeader("Host", host);
}

HTTPHeader HTTPHeader::Location(const URL& locationn)
{
    return HTTPHeader("Location", locationn.str());
}

const std::string& HTTPHeader::name() const
{
    return m_name;
}

const std::string& HTTPHeader::value() const
{
    return m_value;
}

void HTTPHeader::setValue(const std::string& value)
{
    m_value = value;
}

std::string HTTPHeader::toString() const
{
    return (m_name + ": " + m_value);
}
