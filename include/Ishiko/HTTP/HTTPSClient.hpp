// SPDX-FileCopyrightText: 2019-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_HTTP_HTTPSCLIENT_HPP
#define GUARD_ISHIKO_CPP_HTTP_HTTPSCLIENT_HPP

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
    class ConnectionCallbacks : public NetworkConnectionsManager::TLSConnectionCallbacks
    {
    public:
        ConnectionCallbacks(HTTPRequest&& http_request, HTTPResponse& http_response);

        void onConnectionEstablished(NetworkConnectionsManager::ManagedTLSSocket& socket) override;
        void onReadReady() override;
        void onWriteReady() override;

        HTTPRequest m_http_request;
        HTTPResponse& m_http_response;
        NetworkConnectionsManager::ManagedTLSSocket* m_socket;
    };

    NetworkConnectionsManager& m_connection_manager;
    HostnameResolver& m_hostname_resolver;
};

}

#endif
