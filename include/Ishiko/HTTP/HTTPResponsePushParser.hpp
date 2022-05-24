/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPRESPONSEPUSHPARSER_HPP_
#define _ISHIKO_CPP_HTTP_HTTPRESPONSEPUSHPARSER_HPP_

#include <boost/optional.hpp>
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
        virtual void onStatusCode(boost::string_view data);
        virtual void onReasonPhrase(boost::string_view data);
        virtual void onHeader(boost::string_view name, boost::string_view value);
        // TODO: we don't wait for the complete body as it could be very large
        virtual void onBodyFragment(boost::string_view data);
    };

    HTTPMessagePushParser(Callbacks& callbacks);

    bool onData(boost::string_view data);

private:
    enum class ParsingMode
    {
        methodOrHTTPVersion, // We do not know whether we are parsing a request or a response yet
        requestURI,
        // The HTTP version can appear in the request or response so we need 2 different states to distinguish them
        requestHTTPVersion,
        responseHTTPVersion,
        statusCode,
        reasonPhrase,
        headerOrSeparator,
        headerName,
        headerValue,
        separator,
        body
    };

    void notifyHeader();

    ParsingMode m_parsingMode;
    std::string m_fragmentedData1;
    std::string m_fragmentedData2;
    boost::optional<size_t> m_remainingContentLength;
    Callbacks& m_callbacks;
};

}

#endif
