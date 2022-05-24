/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPResponsePushParserTestCallbacks.hpp"

void HTTPResponsePushParserTestCallbacks::onRequest()
{
    m_messageType = MessageType::request;
}

void HTTPResponsePushParserTestCallbacks::onResponse()
{
    m_messageType = MessageType::response;
}

void HTTPResponsePushParserTestCallbacks::onMethod(boost::string_view data)
{
    m_method = data.to_string();
}

void HTTPResponsePushParserTestCallbacks::onRequestURI(boost::string_view data)
{
    m_requestURI = data.to_string();
}

void HTTPResponsePushParserTestCallbacks::onHTTPVersion(boost::string_view data)
{
    m_httpVersion = data.to_string();
}

void HTTPResponsePushParserTestCallbacks::onStatusCode(boost::string_view data)
{
    m_statusCode = data.to_string();
}

void HTTPResponsePushParserTestCallbacks::onReasonPhrase(boost::string_view data)
{
    m_reasonPhrase = data.to_string();
}

void HTTPResponsePushParserTestCallbacks::onHeader(boost::string_view name, boost::string_view value)
{
    m_headers.emplace_back(std::make_pair<std::string, std::string>(name.to_string(), value.to_string()));
}

void HTTPResponsePushParserTestCallbacks::onBodyFragment(boost::string_view data)
{
    m_body.append(data.to_string());
}

HTTPResponsePushParserTestCallbacks::MessageType HTTPResponsePushParserTestCallbacks::messageType() const
{
    return m_messageType;
}

const std::string& HTTPResponsePushParserTestCallbacks::method() const
{
    return m_method;
}

const std::string& HTTPResponsePushParserTestCallbacks::requestURI() const
{
    return m_requestURI;
}

const std::string& HTTPResponsePushParserTestCallbacks::httpVersion() const
{
    return m_httpVersion;
}

const std::string& HTTPResponsePushParserTestCallbacks::statusCode() const
{
    return m_statusCode;
}

const std::string& HTTPResponsePushParserTestCallbacks::reasonPhrase() const
{
    return m_reasonPhrase;
}

const std::vector<std::pair<std::string, std::string>>& HTTPResponsePushParserTestCallbacks::headers() const
{
    return m_headers;
}

const std::string& HTTPResponsePushParserTestCallbacks::body() const
{
    return m_body;
}
