// SPDX-FileCopyrightText: 2019-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "HTTPClient.hpp"
#include "HTTPErrorCategory.hpp"
#include "HTTPResponsePushParser.hpp"
// TODO: spurious header files
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace Ishiko;

HTTPClient::HTTPClient(NetworkConnectionsManager& connection_manager)
    : m_connection_manager{connection_manager}
{
}

void HTTPClient::get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error)
{
    Request callbacks{uri, response};
    m_connection_manager.connect(address, port, callbacks, error);
    m_connection_manager.run();
}

void HTTPClient::Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error)
{
    TCPClientSocket socket(error);
    if (error)
    {
        return;
    }

    socket.connect(address, port, error);
    if (error)
    {
        return;
    }

    HTTPRequest request(HTTPMethod::get, uri);
    //request.setConnectionHeader(HTTPHeader::ConnectionMode::close);
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
    } while ((n != 0) && !error);

    // TODO: is this the correct way to shutdown here?
    // TODO: need to implement these functions in TCPClientSocket
    socket.shutdown(error);
    socket.close();
}

void HTTPClient::Get(IPv4Address address, Port port, const std::string& uri, std::ostream& response, Error& error)
{
    TCPClientSocket socket(error);
    if (error)
    {
        return;
    }

    socket.connect(address, port, error);
    if (error)
    {
        return;
    }

    HTTPRequest request(HTTPMethod::get, uri);
    request.setConnectionHeader(HTTPHeader::ConnectionMode::close);
    std::string requestStr = request.toString();
    socket.write(requestStr.c_str(), requestStr.size(), error);
    if (error)
    {
        return;
    }

    // TODO: buffer size and handle bigger responses
    // TODO: this only works if the server closes the connection after the response is sent. We do set the close header
    // but do we need to be more robust and parse some of the headers.
    char buffer[10 * 1024];
    size_t offset = 0;
    int n = 0;
    do
    {
        n = socket.read(buffer, sizeof(buffer), error);
        response.write(buffer, n);
    } while ((n != 0) && !error);

    // TODO: is this the correct way to shutdown here?
    // TODO: need to implement these functions in TCPClientSocket
    socket.shutdown(error);
    socket.close();
}

void HTTPClient::Get(const std::string& address, unsigned short port, const std::string& uri, HTTPResponse& response,
    Error& error)
{
    IPv4Address ipv4Address(address, error);
    if (!error)
    {
        Get(ipv4Address, port, uri, response, error);
    }
}

void HTTPClient::Get(const std::string& address, unsigned short port, const std::string& uri, std::ostream& response,
    Error& error)
{
    IPv4Address ipv4Address(address, error);
    if (!error)
    {
        Get(ipv4Address, port, uri, response, error);
    }
    
    // TODO: keep this for now because I want to keep this as a tutorial somewhere
#if 0
    try
    {
        asio::io_context ioContext;
        asio::ip::tcp::socket socket(ioContext);

        system::error_code ec;
        asio::ip::tcp::endpoint endpoint(asio::ip::make_address(address), port);
        socket.connect(endpoint, ec);
        if (!ec)
        {
            beast::http::request<beast::http::string_body> request(beast::http::verb::get, uri, 11);
            beast::http::write(socket, request, ec);
            if (!ec)
            {
                beast::flat_buffer buffer;
                beast::http::response<beast::http::dynamic_body> res;
                beast::http::read(socket, buffer, res, ec);
                if (!ec)
                {
                    response << res;
                }
            }

            // We ignore failure to shutdwon gracefully. It is not clear what a client would be expected to do in this
            // case and the request was sent successfully anyway.
            system::error_code ignore;
            socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignore);
        }

        if (ec)
        {
            // TODO : proper error message
            Fail(error, HTTPErrorCategory::Value::generic, "", __FILE__, __LINE__);
        }
    }
    catch (...)
    {
        // TODO : proper error message
        Fail(error, HTTPErrorCategory::Value::generic, "", __FILE__, __LINE__);
    }
#endif
}

HTTPClient::Request::Request(const std::string& uri, HTTPResponse& response)
    : m_request{HTTPMethod::get, uri}, m_response{response}
{
    // TODO
    m_request.setConnectionHeader(HTTPHeader::ConnectionMode::close);
}

void HTTPClient::Request::onConnectionEstablished(TCPClientSocket& socket)
{
    // TODO:how do we handle errors?
    Error todo_ignored_error;

    std::string requestStr = m_request.toString();
    socket.write(requestStr.c_str(), requestStr.size(), todo_ignored_error);
    if (todo_ignored_error)
    {
        return;
    }
}

void HTTPClient::Request::onData(boost::string_view data)
{
    HTTPResponse::ParserCallbacks callbacks(m_response);
    HTTPResponsePushParser parser(callbacks);

    parser.onData(boost::string_view(data));
}
