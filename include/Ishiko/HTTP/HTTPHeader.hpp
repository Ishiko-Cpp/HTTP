/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPHEADER_HPP_
#define _ISHIKO_CPP_HTTP_HTTPHEADER_HPP_

#include <string>

namespace Ishiko
{

class HTTPHeader
{
public:
    HTTPHeader(std::string name, std::string value);

    const std::string& name() const;
    const std::string& value() const;

private:
    std::string m_name;
    std::string m_value;
};

}

#endif
