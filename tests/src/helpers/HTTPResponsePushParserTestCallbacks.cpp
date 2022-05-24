/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPResponsePushParserTestCallbacks.hpp"

void HTTPMessagePushParserTestCallbacks::onRequest()
{
    m_messageType = MessageType::request;
}

void HTTPMessagePushParserTestCallbacks::onResponse()
{
    m_messageType = MessageType::response;
}

void HTTPMessagePushParserTestCallbacks::onMethod(boost::string_view data)
{
    m_method = data.to_string();
}

void HTTPMessagePushParserTestCallbacks::onRequestURI(boost::string_view data)
{
    m_requestURI = data.to_string();
}

void HTTPMessagePushParserTestCallbacks::onHTTPVersion(boost::string_view data)
{
    m_httpVersion = data.to_string();
}

void HTTPMessagePushParserTestCallbacks::onStatusCode(boost::string_view data)
{
    m_statusCode = data.to_string();
}

void HTTPMessagePushParserTestCallbacks::onReasonPhrase(boost::string_view data)
{
    m_reasonPhrase = data.to_string();
}

void HTTPMessagePushParserTestCallbacks::onHeader(boost::string_view name, boost::string_view value)
{
    m_headers.emplace_back(std::make_pair<std::string, std::string>(name.to_string(), value.to_string()));
}

void HTTPMessagePushParserTestCallbacks::onBodyFragment(boost::string_view data)
{
    m_body.append(data.to_string());
}

HTTPMessagePushParserTestCallbacks::MessageType HTTPMessagePushParserTestCallbacks::messageType() const
{
    return m_messageType;
}

const std::string& HTTPMessagePushParserTestCallbacks::method() const
{
    return m_method;
}

const std::string& HTTPMessagePushParserTestCallbacks::requestURI() const
{
    return m_requestURI;
}

const std::string& HTTPMessagePushParserTestCallbacks::httpVersion() const
{
    return m_httpVersion;
}

const std::string& HTTPMessagePushParserTestCallbacks::statusCode() const
{
    return m_statusCode;
}

const std::string& HTTPMessagePushParserTestCallbacks::reasonPhrase() const
{
    return m_reasonPhrase;
}

const std::vector<std::pair<std::string, std::string>>& HTTPMessagePushParserTestCallbacks::headers() const
{
    return m_headers;
}

const std::string& HTTPMessagePushParserTestCallbacks::body() const
{
    return m_body;
}
