/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPHeader.hpp"
#include <boost/date_time.hpp>

using namespace std;

namespace Ishiko
{

HTTPHeader::HTTPHeader(string name, string value)
    : m_name(move(name)), m_value(move(value))
{
}

HTTPHeader HTTPHeader::Date(const UTCTime& time)
{
    return HTTPHeader("Date", time.toRFC7231String());
}

HTTPHeader HTTPHeader::Location(const URL& locationn)
{
    return HTTPHeader("Location", locationn.str());
}

const string& HTTPHeader::name() const
{
    return m_name;
}

const string& HTTPHeader::value() const
{
    return m_value;
}

string HTTPHeader::toString() const
{
    return (m_name + ": " + m_value);
}

}
