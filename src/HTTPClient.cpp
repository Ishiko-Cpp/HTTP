/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPClient.hpp"
#include "ErrorCategory.hpp"
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace boost;

namespace Ishiko
{
namespace HTTP
{

void HTTPClient::Get(const std::string& address, unsigned short port, const std::string& uri, std::ostream& response,
    Ishiko::Error& error)
{
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
            Fail(error, ErrorCategory::Value::generic, "", __FILE__, __LINE__);
        }
    }
    catch (...)
    {
        // TODO : proper error message
        Fail(error, ErrorCategory::Value::generic, "", __FILE__, __LINE__);
    }
}

}
}
