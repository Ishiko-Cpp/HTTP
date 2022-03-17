/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HELPERS_HTTPMESSAGEPUSHPARSERTESTCALLBACKS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HELPERS_HTTPMESSAGEPUSHPARSERTESTCALLBACKS_HPP_

#include "Ishiko/HTTP/HTTPMessagePushParser.hpp"
#include <string>
#include <utility>
#include <vector>

class HTTPMessagePushParserTestCallbacks : public Ishiko::HTTPMessagePushParser::Callbacks
{
public:
    void onMethod(boost::string_view data) override;
    void onRequestURI(boost::string_view data) override;
    void onHTTPVersion(boost::string_view data) override;
    void onHeader(boost::string_view name, boost::string_view value) override;

    const std::string method() const;
    const std::string requestURI() const;
    const std::string httpVersion() const;
    const std::vector<std::pair<std::string, std::string>>& headers() const;

private:
    std::string m_method;
    std::string m_requestURI;
    std::string m_httpVersion;
    std::vector<std::pair<std::string, std::string>> m_headers;
};

#endif
