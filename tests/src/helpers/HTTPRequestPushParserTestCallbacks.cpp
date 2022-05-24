/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPRequestPushParserTestCallbacks.hpp"

void HTTPRequestPushParserTestCallbacks::onRequest()
{
    m_messageType = MessageType::request;
}

void HTTPRequestPushParserTestCallbacks::onResponse()
{
    m_messageType = MessageType::response;
}

void HTTPRequestPushParserTestCallbacks::onMethod(boost::string_view data)
{
    m_method = data.to_string();
}

void HTTPRequestPushParserTestCallbacks::onRequestURI(boost::string_view data)
{
    m_requestURI = data.to_string();
}

void HTTPRequestPushParserTestCallbacks::onHTTPVersion(boost::string_view data)
{
    m_httpVersion = data.to_string();
}

void HTTPRequestPushParserTestCallbacks::onStatusCode(boost::string_view data)
{
    m_statusCode = data.to_string();
}

void HTTPRequestPushParserTestCallbacks::onReasonPhrase(boost::string_view data)
{
    m_reasonPhrase = data.to_string();
}

void HTTPRequestPushParserTestCallbacks::onHeader(boost::string_view name, boost::string_view value)
{
    m_headers.emplace_back(std::make_pair<std::string, std::string>(name.to_string(), value.to_string()));
}

void HTTPRequestPushParserTestCallbacks::onBodyFragment(boost::string_view data)
{
    m_body.append(data.to_string());
}

HTTPRequestPushParserTestCallbacks::MessageType HTTPRequestPushParserTestCallbacks::messageType() const
{
    return m_messageType;
}

const std::string& HTTPRequestPushParserTestCallbacks::method() const
{
    return m_method;
}

const std::string& HTTPRequestPushParserTestCallbacks::requestURI() const
{
    return m_requestURI;
}

const std::string& HTTPRequestPushParserTestCallbacks::httpVersion() const
{
    return m_httpVersion;
}

const std::string& HTTPRequestPushParserTestCallbacks::statusCode() const
{
    return m_statusCode;
}

const std::string& HTTPRequestPushParserTestCallbacks::reasonPhrase() const
{
    return m_reasonPhrase;
}

const std::vector<std::pair<std::string, std::string>>& HTTPRequestPushParserTestCallbacks::headers() const
{
    return m_headers;
}

const std::string& HTTPRequestPushParserTestCallbacks::body() const
{
    return m_body;
}
