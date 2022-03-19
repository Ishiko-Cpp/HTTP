/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPMethod.hpp"

using namespace std;

namespace Ishiko
{

HTTPMethod::HTTPMethod(Value value)
    : m_value(value)
{
}

bool HTTPMethod::operator==(HTTPMethod other) const
{
    return (m_value == other.m_value);
}

bool HTTPMethod::operator!=(HTTPMethod other) const
{
    return (m_value != other.m_value);
}

string HTTPMethod::toString() const
{
    switch (m_value)
    {
    case get:
        return "GET";

    default:
        // TODO
        return "";
    }
}

}
