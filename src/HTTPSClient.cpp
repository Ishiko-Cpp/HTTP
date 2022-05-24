/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPRequest.hpp"
#include "HTTPResponsePushParser.hpp"
#include "HTTPSClient.hpp"

using namespace Ishiko;

void HTTPSClient::Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error)
{
    HTTPRequest request(HTTPMethod::get, uri);

    TLSClientSocket socket(error);
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
