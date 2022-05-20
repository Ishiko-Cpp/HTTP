/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPHeaders.hpp"

using namespace Ishiko;

size_t HTTPHeaders::size() const noexcept
{
    return m_headers.size();
}

void HTTPHeaders::push_back(const HTTPHeader& header)
{
    m_headers.push_back(header);
}

void HTTPHeaders::push_back(const std::string& name, const std::string& value)
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
