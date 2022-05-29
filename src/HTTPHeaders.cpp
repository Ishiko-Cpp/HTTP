/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPHeaders.hpp"
#include "HTTPErrorCategory.hpp"

using namespace Ishiko;

size_t HTTPHeaders::size() const noexcept
{
    return m_headers.size();
}

const HTTPHeader& HTTPHeaders::at(const std::string& name) const
{
    for (const HTTPHeader& header : m_headers)
    {
        if (header.name() == name)
        {
            return header;
        }
    }

    // TODO: throw appropriate exception
    throw std::range_error("");
}

void HTTPHeaders::set(const HTTPHeader& header)
{
    for (HTTPHeader& existingHeader : m_headers)
    {
        if (existingHeader.name() == header.name())
        {
            existingHeader.setValue(header.value());
            return;
        }
    }
    m_headers.push_back(header);
}

void HTTPHeaders::set(const std::string& name, const std::string& value)
{
    for (HTTPHeader& existingHeader : m_headers)
    {
        if (existingHeader.name() == name)
        {
            existingHeader.setValue(value);
            return;
        }
    }
    m_headers.emplace_back(name, value);
}

void HTTPHeaders::pushBack(const HTTPHeader& header)
{
    m_headers.push_back(header);
}

void HTTPHeaders::pushBack(const std::string& name, const std::string& value)
{
    m_headers.emplace_back(name, value);
}

HTTPHeaders::const_iterator HTTPHeaders::begin() const noexcept
{
    return m_headers.begin();
}

HTTPHeaders::iterator HTTPHeaders::begin() noexcept
{
    return m_headers.begin();
}

HTTPHeaders::const_iterator HTTPHeaders::end() const noexcept
{
    return m_headers.end();
}

HTTPHeaders::iterator HTTPHeaders::end() noexcept
{
    return m_headers.end();
}
