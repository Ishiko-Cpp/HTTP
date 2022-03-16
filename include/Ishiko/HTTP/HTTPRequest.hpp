/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPREQUEST_HPP_
#define _ISHIKO_CPP_HTTP_HTTPREQUEST_HPP_

namespace Ishiko
{

class HTTPRequest
{
public:
    enum class Method
    {
        get
    };

    HTTPRequest(Method method);

    Method method() const;

private:
    Method m_method;
};

}

#endif
