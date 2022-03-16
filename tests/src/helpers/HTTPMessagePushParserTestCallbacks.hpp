/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_HTTP_TESTS_HELPERS_HTTPMESSAGEPUSHPARSERTESTCALLBACKS_HPP_
#define _ISHIKO_HTTP_TESTS_HELPERS_HTTPMESSAGEPUSHPARSERTESTCALLBACKS_HPP_

#include "Ishiko/HTTP/HTTPMessagePushParser.hpp"

class HTTPMessagePushParserTestCallbacks : public Ishiko::HTTPMessagePushParser::Callbacks
{
public:
    void onMethod(boost::string_view data) override;
    void onRequestURI(boost::string_view data) override;
    void onHTTPVersion(boost::string_view data) override;

    const std::string method() const;
    const std::string requestURI() const;
    const std::string httpVersion() const;

private:
    std::string m_method;
    std::string m_requestURI;
    std::string m_httpVersion;
};

#endif
