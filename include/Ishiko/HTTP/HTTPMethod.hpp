/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPMETHOD_HPP_
#define _ISHIKO_CPP_HTTP_HTTPMETHOD_HPP_

#include <string>

namespace Ishiko
{

class HTTPMethod
{
public:
    enum Value
    {
        get
    };

    HTTPMethod(Value value);

    bool operator==(HTTPMethod other) const;
    bool operator!=(HTTPMethod other) const;

    std::string toString() const;

private:
    Value m_value;
};

}

#endif
