/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HELPERS_HTTPRESPONSEPUSHPARSERTESTCALLBACKS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HELPERS_HTTPRESPONSEPUSHPARSERTESTCALLBACKS_HPP_

#include "Ishiko/HTTP/HTTPResponsePushParser.hpp"
#include <string>
#include <utility>
#include <vector>

class HTTPMessagePushParserTestCallbacks : public Ishiko::HTTPMessagePushParser::Callbacks
{
public:
    enum class MessageType
    {
        uninitialized,
        request,
        response
    };

    void onRequest() override;
    void onResponse() override;
    void onMethod(boost::string_view data) override;
    void onRequestURI(boost::string_view data) override;
    void onHTTPVersion(boost::string_view data) override;
    void onStatusCode(boost::string_view data) override;
    void onReasonPhrase(boost::string_view data) override;
    void onHeader(boost::string_view name, boost::string_view value) override;
    void onBodyFragment(boost::string_view data) override;

    MessageType messageType() const;
    const std::string& method() const;
    const std::string& requestURI() const;
    const std::string& httpVersion() const;
    const std::string& statusCode() const;
    const std::string& reasonPhrase() const;
    const std::vector<std::pair<std::string, std::string>>& headers() const;
    const std::string& body() const;

private:
    MessageType m_messageType = MessageType::uninitialized;
    std::string m_method;
    std::string m_requestURI;
    std::string m_httpVersion;
    std::string m_statusCode;
    std::string m_reasonPhrase;
    std::vector<std::pair<std::string, std::string>> m_headers;
    std::string m_body;
};

#endif
