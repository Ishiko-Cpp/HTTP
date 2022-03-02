/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "HTTPClient.h"
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace boost;

namespace Ishiko
{
namespace HTTP
{

void HTTPClient::get(const std::string& address, unsigned short port, const std::string& uri, std::ostream& response,
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
            error.fail(-1, "", __FILE__, __LINE__);
        }
    }
    catch (...)
    {
        // TODO : proper error message
        error.fail(-1, "", __FILE__, __LINE__);
    }
}

}
}
