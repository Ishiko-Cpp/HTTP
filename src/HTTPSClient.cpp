/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPRequest.hpp"
#include "HTTPMessagePushParser.hpp"
#include "HTTPSClient.hpp"

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

void HTTPSClient::Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error)
{
    TLSClientSocket socket(error);
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
    //socket.shutdown(error);
    //socket.close();
}
