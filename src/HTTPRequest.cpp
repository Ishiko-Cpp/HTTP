/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPRequest.hpp"

namespace Ishiko
{

HTTPRequest::HTTPRequest(Method method)
    : m_method(method)
{
}

HTTPRequest::Method HTTPRequest::method() const
{
    return m_method;
}

}
