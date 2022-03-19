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
    enum Value
    {
        ok = 200,
        movedPermanently = 301,
        badRequest = 400,
        notFound = 404,
        internalServerError = 500
    };

    HTTPStatusCode(Value value);

    std::string getReasonPhrase() const;

    bool operator==(unsigned int value) const;
    bool operator!=(unsigned int value) const;

    std::string toString() const;

private:
    Value m_value;
};

}

#endif
