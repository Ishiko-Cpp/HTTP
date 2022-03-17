/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPSTATUSCODE_HPP_
#define _ISHIKO_CPP_HTTP_HTTPSTATUSCODE_HPP_

#include <string>

namespace Ishiko
{

class HTTPStatusCode
{
public:
    HTTPStatusCode();

    std::string getReasonPhrase() const;

    std::string toString() const;
};

}

#endif
