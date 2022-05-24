/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPResponsePushParserTestCallbacks.hpp"

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
