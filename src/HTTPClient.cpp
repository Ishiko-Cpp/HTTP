/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPClient.hpp"
#include "HTTPErrorCategory.hpp"
#include "HTTPMessagePushParser.hpp"
#include "HTTPRequest.hpp"
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace Ishiko;

namespace
{

// TODO: this seems generic enough for it to be a public API
class HTTPClientResponseParserCallbacks : public HTTPMessagePushParser::Callbacks
{
public:
    HTTPClientResponseParserCallbacks(HTTPResponse& response);

    void onStatusCode(boost::string_view data) override;
    void onReasonPhrase(boost::string_view data) override;
    void onHeader(boost::string_view name, boost::string_view value) override;

private:
    HTTPResponse& m_response;
};

HTTPClientResponseParserCallbacks::HTTPClientResponseParserCallbacks(HTTPResponse& response)
    : m_response(response)
{
}

void HTTPClientResponseParserCallbacks::onStatusCode(boost::string_view data)
{
    // TODO: handle error
    Error error;
    HTTPStatusCode statusCode(data.to_string(), error); // TODO: avoid to_string
    m_response.setStatusCode(statusCode);
}

void HTTPClientResponseParserCallbacks::onReasonPhrase(boost::string_view data)
{
    // TODO: do I store this only if it is different from the default?
}

void HTTPClientResponseParserCallbacks::onHeader(boost::string_view name, boost::string_view value)
{
    m_response.appendHeader(name.to_string(), value.to_string());   // TODO: avoid to_string.
}

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
    request.setConnectionHeader(HTTPHeader::ConnectionMode::close);
    std::string requestStr = request.toString();
    socket.write(requestStr.c_str(), requestStr.size(), error);
    if (error)
    {
        return;
    }

    HTTPClientResponseParserCallbacks callbacks(response);
    HTTPMessagePushParser parser(callbacks);

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
