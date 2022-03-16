/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPMessagePushParserTestCallbacks.hpp"

using namespace std;

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

const string HTTPMessagePushParserTestCallbacks::method() const
{
    return m_method;
}

const string HTTPMessagePushParserTestCallbacks::requestURI() const
{
    return m_requestURI;
}

const string HTTPMessagePushParserTestCallbacks::httpVersion() const
{
    return m_httpVersion;
}
