// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_HTTP_HTTPSCLIENT_HPP
#define GUARD_ISHIKO_CPP_HTTP_HTTPSCLIENT_HPP

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include <Ishiko/Errors.hpp>
#include <Ishiko/Networking.hpp>
#include <string>

namespace Ishiko
{

class HTTPSClient
{
public:
    HTTPSClient(NetworkConnectionsManager& connection_manager, HostnameResolver& hostname_resolver);

    void get(Hostname hostname, Port port, const std::string& uri, HTTPResponse& response, Error& error);

    // TODO: the URI host part will be used to set SNI
    static void Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error);

private:
    class ConnectionCallbacks : public AsyncTLSClientSocket::Callbacks
    {
    public:
        ConnectionCallbacks(HTTPRequest&& http_request, HTTPResponse& http_response);

        void onConnectionEstablished(const Error& error, AsyncTLSClientSocket& socket) override;
        void onHandshake(const Error& error, AsyncTLSClientSocket& socket) override;
        void onReadReady(const Error& error, AsyncTLSClientSocket& socket) override;
        void onWriteReady(const Error& error, AsyncTLSClientSocket& socket) override;

        HTTPRequest m_http_request;
        HTTPResponse& m_http_response;
    };

    NetworkConnectionsManager& m_connection_manager;
    HostnameResolver& m_hostname_resolver;
};

}

#endif
