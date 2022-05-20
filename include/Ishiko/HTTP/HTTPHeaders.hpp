/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HEADERS_HPP_
#define _ISHIKO_CPP_HTTP_HEADERS_HPP_

#include "HTTPHeader.hpp"
#include <vector>

namespace Ishiko
{

class HTTPHeaders
{
public:
    typedef std::vector<HTTPHeader>::const_iterator const_iterator;
    typedef std::vector<HTTPHeader>::iterator iterator;

    size_t size() const noexcept;

    void push_back(const HTTPHeader& header);
    void push_back(const std::string& name, const std::string& value);

    const_iterator begin() const noexcept;
    iterator begin() noexcept;
    const_iterator end() const noexcept;
    iterator end() noexcept;

private:
    std::vector<HTTPHeader> m_headers;
};

}

#endif
