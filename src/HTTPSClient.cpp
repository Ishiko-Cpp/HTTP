// SPDX-FileCopyrightText: 2022-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "HTTPRequest.hpp"
#include "HTTPResponsePushParser.hpp"
#include "HTTPSClient.hpp"

using namespace Ishiko;

HTTPSClient::HTTPSClient(NetworkConnectionsManager& connection_manager, HostnameResolver& hostname_resolver)
    : m_connection_manager{connection_manager}, m_hostname_resolver{hostname_resolver}
{
}

void HTTPSClient::get(Hostname hostname, Port port, const std::string& uri, HTTPResponse& response, Error& error)
{
    std::vector<IPv4Address> ip_addresses;
    m_hostname_resolver.resolve(hostname, ip_addresses, error);
    if (!error)
    {
        HTTPRequest http_request{HTTPMethod::get, uri};
        http_request.setHostHeader(hostname.asString());
        http_request.setConnectionHeader(HTTPHeader::ConnectionMode::close);

        ConnectionCallbacks callbacks{std::move(http_request), response};
        // TODO: for now just use first address
        m_connection_manager.connectWithTLS(ip_addresses[0], port, hostname, callbacks, error);
        m_connection_manager.run(
            [](NetworkConnectionsManager& connections_manager)
            {
                return connections_manager.idle();
            });
    }
}

void HTTPSClient::Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error)
{
    HTTPRequest request(HTTPMethod::get, uri);

    TLSClientSocket socket(SocketOption::none, error);
    if (error)
    {
        return;
    }

    std::string hostname;
    if (request.requestURI().host())
    {
        hostname = *request.requestURI().host();
    }
    socket.connect(address, port, hostname, error);
    if (error)
    {
        return;
    }

    socket.handshake(error);
    if (error)
    {
        return;
    }

    request.setConnectionHeader(HTTPHeader::ConnectionMode::close);
    std::string requestStr = request.toString();
    socket.write(requestStr.c_str(), requestStr.size(), error);
    if (error)
    {
        return;
    }

    HTTPResponse::ParserCallbacks callbacks(response);
    HTTPResponsePushParser parser(callbacks);

    // TODO: buffer size and handle bigger responses
    // TODO: this only works if the server closes the connection after the response is sent. We do set the close header
    // but since we are parsing already can we double check stuff and also create APIs that support connection re-use.
    char buffer[10 * 1024];
    size_t offset = 0;
    int n = 0;
    do
    {
        n = socket.read(buffer, sizeof(buffer), error);
        parser.onData(boost::string_view(buffer, n));
    }
    while ((n != 0) && !error);

    // TODO: is this the correct way to shutdown here?
    // TODO: need to implement these functions in TCPClientSocket
    //socket.shutdown(error);
    //socket.close();
}

HTTPSClient::ConnectionCallbacks::ConnectionCallbacks(HTTPRequest&& http_request, HTTPResponse& http_response)
    : m_http_request{std::move(http_request)}, m_http_response{http_response}
{
}

void HTTPSClient::ConnectionCallbacks::onConnectionEstablished(NetworkConnectionsManager::ManagedTLSSocket& socket)
{
    m_socket = &socket;

    Error error;
    m_socket->handshake(error);
    // TODO: always assyme error for now
}

void HTTPSClient::ConnectionCallbacks::onHandshake()
{
    // TODO:how do we handle errors?
    Error todo_ignored_error;

    std::string requestStr = m_http_request.toString();
    m_socket->write(requestStr.c_str(), requestStr.size(), todo_ignored_error);
    if (todo_ignored_error)
    {
        return;
    }

    // TODO: these errors need to be reported to the clients somehow
    Error todo_error;

    // TODO: to trigger error, normally would check error but for test for now we know it will be EAGAIN
    char buffer[10 * 1024];
    size_t offset = 0;
    int n = m_socket->read(buffer, sizeof(buffer), todo_error);
    // TODO
    if (!todo_error)
    {
        HTTPResponse::ParserCallbacks callbacks(m_http_response);
        HTTPResponsePushParser parser(callbacks);
        parser.onData(boost::string_view(buffer, n));
        // TODO: is this the correct way to shutdown here?
        // TODO: need to implement these functions in TCPClientSocket
        m_socket->shutdown(todo_error);
        m_socket->close();
    }
}

void HTTPSClient::ConnectionCallbacks::onReadReady()
{
    // TODO: these errors need to be reported to the clients somehow
    Error todo_error;

    HTTPResponse::ParserCallbacks callbacks(m_http_response);
    HTTPResponsePushParser parser(callbacks);

    // TODO: buffer size and handle bigger responses
    // TODO: this only works if the server closes the connection after the response is sent. We do set the close header
    // but since we are parsing already can we double check stuff and also create APIs that support connection re-use.
    char buffer[10 * 1024];
    size_t offset = 0;
    int n = 0;
    do
    {
        // TODO: assume there is only one read because these could all block again
        n = m_socket->read(buffer, sizeof(buffer), todo_error);
        parser.onData(boost::string_view(buffer, n));
    } while ((n != 0) && !todo_error);

    // TODO: is this the correct way to shutdown here?
    // TODO: need to implement these functions in TCPClientSocket
    m_socket->shutdown(todo_error);
    m_socket->close();
}

void HTTPSClient::ConnectionCallbacks::onWriteReady()
{
}
