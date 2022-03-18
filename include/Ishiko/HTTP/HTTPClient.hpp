/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPCLIENT_HPP_
#define _ISHIKO_CPP_HTTP_HTTPCLIENT_HPP_

#include <Ishiko/Networking.hpp>
#include <Ishiko/Errors.hpp>
#include <ostream>
#include <string>

namespace Ishiko
{

class HTTPClient
{
public:
    static void Get(IPv4Address address, Port port, const std::string& uri, std::ostream& response, Error& error);
    static void Get(const std::string& address, unsigned short port, const std::string& uri, std::ostream& response,
        Error& error);
};

}

#endif
