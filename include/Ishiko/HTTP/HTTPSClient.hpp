/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPSCLIENT_HPP_
#define _ISHIKO_CPP_HTTP_HTTPSCLIENT_HPP_

#include "HTTPResponse.hpp"
#include <Ishiko/Errors.hpp>
#include <Ishiko/Networking.hpp>
#include <string>

namespace Ishiko
{

class HTTPSClient
{
public:
    static void Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error);
};

}

#endif
