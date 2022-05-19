/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPMESSAGEPUSHPARSER_HPP_
#define _ISHIKO_CPP_HTTP_HTTPMESSAGEPUSHPARSER_HPP_

#include <boost/utility/string_view.hpp>

namespace Ishiko
{

class HTTPMessagePushParser
{
public:
    class Callbacks
    {
    public:
        virtual ~Callbacks() = default;

        virtual void onRequest();
        virtual void onResponse();
        virtual void onMethod(boost::string_view data);
        virtual void onRequestURI(boost::string_view data);
        virtual void onHTTPVersion(boost::string_view data);
        virtual void onHeader(boost::string_view name, boost::string_view value);
        virtual void onBody(boost::string_view data);
    };

    HTTPMessagePushParser(Callbacks& callbacks);

    bool onData(boost::string_view data);

private:
    enum class ParsingMode
    {
        methodOrHTTPVersion, // We do not know whether we are parsing a request or a response yet
        requestURI,
        httpVersion,
        headerOrSeparator,
        headerName,
        headerValue,
        separator,
        body
    };

    void notifyHeader();

    ParsingMode m_parsingMode = ParsingMode::methodOrHTTPVersion;
    std::string m_fragmentedData1;
    std::string m_fragmentedData2;
    Callbacks& m_callbacks;
};

}

#endif
