// SPDX-FileCopyrightText: 2019-2024 Xavier Leclercq
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
        HTTPClient(NetworkConnectionsManager& connection_manager);

        // TODO: maybe using a std::future here would be nice? It does look like a good fit.
        void get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error);

        // TODO: have these static functions become a problem?
        static void Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error);
        static void Get(IPv4Address address, Port port, const std::string& uri, std::ostream& response, Error& error);
        static void Get(const std::string& address, unsigned short port, const std::string& uri,
            HTTPResponse& response, Error& error);
        static void Get(const std::string& address, unsigned short port, const std::string& uri,
            std::ostream& response, Error& error);

    private:
        // TODO: think about a better name for this class
        class Request : public NetworkConnectionsManager::ConnectionCallbacks
        {
        public:
            Request(const std::string& uri, HTTPResponse& response);

            void onConnectionEstablished(NetworkConnectionsManager::ManagedSocket& socket) override;
            void onData(boost::string_view data) override;
            void onWrite() override;

            HTTPRequest m_request;
            HTTPResponse& m_response;
        };

        NetworkConnectionsManager& m_connection_manager;
    };
}

#endif
