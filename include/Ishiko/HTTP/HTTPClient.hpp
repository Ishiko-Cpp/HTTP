// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_HTTP_HTTPCLIENT_HPP
#define GUARD_ISHIKO_CPP_HTTP_HTTPCLIENT_HPP

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include <Ishiko/Networking.hpp>
#include <Ishiko/Errors.hpp>
#include <ostream>
#include <string>

namespace Ishiko
{
    class HTTPClient
    {
    public:
        HTTPClient(NetworkConnectionsManager& connection_manager, HostnameResolver& hostname_resolver);

        // TODO: maybe using a std::future here would be nice? It does look like a good fit.
        // TODO: At the moment this function is blocking/synchronous though
        void get(Hostname hostname, Port port, const std::string& uri, HTTPResponse& response, Error& error);
        void get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error);

        // TODO: have these static functions become a problem?
        static void Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error);
        static void Get(IPv4Address address, Port port, const std::string& uri, std::ostream& response, Error& error);
        static void Get(const std::string& address, unsigned short port, const std::string& uri,
            HTTPResponse& response, Error& error);
        static void Get(const std::string& address, unsigned short port, const std::string& uri,
            std::ostream& response, Error& error);

    private:
        class ConnectionCallbacks : public AsyncTCPClientSocket::Callbacks
        {
        public:
            ConnectionCallbacks(HTTPRequest&& http_request, HTTPResponse& http_response);

            void onConnectionEstablished(const Error& error, AsyncTCPClientSocket& socket) override;
            void onReadReady(const Error& error, AsyncTCPClientSocket& socket) override;
            void onWriteReady(const Error& error, AsyncTCPClientSocket& socket) override;

            HTTPRequest m_http_request;
            HTTPResponse& m_http_response;
        };

        NetworkConnectionsManager& m_connection_manager;
        HostnameResolver& m_hostname_resolver;
    };
}

#endif
