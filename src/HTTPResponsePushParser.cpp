/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPResponsePushParser.hpp"
#include <Ishiko/Text.hpp>

using namespace Ishiko;

void HTTPResponsePushParser::Callbacks::onRequest()
{
}

void HTTPResponsePushParser::Callbacks::onResponse()
{
}

void HTTPResponsePushParser::Callbacks::onMethod(boost::string_view data)
{
}

void HTTPResponsePushParser::Callbacks::onRequestURI(boost::string_view data)
{
}

void HTTPResponsePushParser::Callbacks::onHTTPVersion(boost::string_view data)
{
}

void HTTPResponsePushParser::Callbacks::onStatusCode(boost::string_view data)
{
}

void HTTPResponsePushParser::Callbacks::onReasonPhrase(boost::string_view data)
{
}

void HTTPResponsePushParser::Callbacks::onHeader(boost::string_view name, boost::string_view value)
{
}

void HTTPResponsePushParser::Callbacks::onBodyFragment(boost::string_view data)
{
}

HTTPResponsePushParser::HTTPResponsePushParser(Callbacks& callbacks)
    : m_parsingMode(ParsingMode::methodOrHTTPVersion), m_callbacks(callbacks)
{
}

// TODO: if pipelining is used then returning bool is not enough since we may have unused bytes at the end of data
bool HTTPResponsePushParser::onData(boost::string_view data)
{
    const char* previous = data.data();
    const char* current = previous;
    const char* end = current + data.length();
    const char* headerNameBegin = nullptr;
    const char* headerNameEnd = nullptr;
    while (current < end)
    {
        switch (m_parsingMode)
        {
        case ParsingMode::methodOrHTTPVersion:
            while (current < end)
            {
                if (*current == ' ')
                {
                    // We have reached the end of the token without encountering a '/' so this a method and we are
                    // parsing a request
                    m_callbacks.onRequest();
                    if (m_fragmentedData1.empty())
                    {
                        m_callbacks.onMethod(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData1.append(data.data(), current - data.data());
                        m_callbacks.onMethod(m_fragmentedData1);
                        m_fragmentedData1.clear();
                    }
                    m_parsingMode = ParsingMode::requestURI;
                    break;
                } 
                else if (*current == '/')
                {
                    // Methods can't have a '/' in them so this is a protocol version and hence we are parsing a response
                    m_callbacks.onResponse();
                    m_parsingMode = ParsingMode::responseHTTPVersion;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData1.append(previous, (current - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::requestURI:
            previous = current;
            while (current < end)
            {
                if (*current == ' ')
                {
                    if (m_fragmentedData1.empty())
                    {
                        m_callbacks.onRequestURI(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData1.append(data.data(), current - data.data());
                        m_callbacks.onRequestURI(m_fragmentedData1);
                        m_fragmentedData1.clear();
                    }
                    m_parsingMode = ParsingMode::requestHTTPVersion;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData1.append(previous, (current - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::requestHTTPVersion:
            previous = current;
            while (current < end)
            {
                if (*current == '\r')
                {
                    if (m_fragmentedData1.empty())
                    {
                        m_callbacks.onHTTPVersion(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData1.append(data.data(), current - data.data());
                        m_callbacks.onHTTPVersion(m_fragmentedData1);
                        m_fragmentedData1.clear();
                    }
                }
                else if (*current == '\n')
                {
                    m_parsingMode = ParsingMode::headerOrSeparator;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                // TODO: handle case where data size is 0
                const char* adjustedCurrent = current;
                if (*(current - 1) == '\r')
                {
                    --adjustedCurrent;
                }
                m_fragmentedData1.append(previous, (adjustedCurrent - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::responseHTTPVersion:
            // We do not set the previous pointer here as the ParsingMode::methodOrHTTPVersion state handler has
            // partially processed it
            while (current < end)
            {
                if (*current == ' ')
                {
                    if (m_fragmentedData1.empty())
                    {
                        m_callbacks.onHTTPVersion(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData1.append(data.data(), current - data.data());
                        m_callbacks.onHTTPVersion(m_fragmentedData1);
                        m_fragmentedData1.clear();
                    }
                    m_parsingMode = ParsingMode::statusCode;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData1.append(previous, (current - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::statusCode:
            previous = current;
            while (current < end)
            {
                if (*current == ' ')
                {
                    if (m_fragmentedData1.empty())
                    {
                        m_callbacks.onStatusCode(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData1.append(data.data(), current - data.data());
                        m_callbacks.onStatusCode(m_fragmentedData1);
                        m_fragmentedData1.clear();
                    }
                    m_parsingMode = ParsingMode::reasonPhrase;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData1.append(previous, (current - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::reasonPhrase:
            previous = current;
            while (current < end)
            {
                if (*current == '\r')
                {
                    if (m_fragmentedData1.empty())
                    {
                        m_callbacks.onReasonPhrase(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData1.append(data.data(), current - data.data());
                        m_callbacks.onReasonPhrase(m_fragmentedData1);
                        m_fragmentedData1.clear();
                    }
                }
                else if (*current == '\n')
                {
                    m_parsingMode = ParsingMode::headerOrSeparator;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                // TODO: handle case where data size is 0
                const char* adjustedCurrent = current;
                if (*(current - 1) == '\r')
                {
                    --adjustedCurrent;
                }
                m_fragmentedData1.append(previous, (adjustedCurrent - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::headerOrSeparator:
            if (*current == '\r')
            {
                m_parsingMode = ParsingMode::separator;
                ++current;
            }
            else if (*current != '\r')
            {
                m_parsingMode = ParsingMode::headerName;
            }
            break;

        case ParsingMode::headerName:
            previous = current;
            while (current < end)
            {
                if (*current == ':')
                {
                    // TODO: I think there is an issue if we reach the end of the current data after we parse ":"
                    headerNameBegin = previous;
                    headerNameEnd = current;
                    m_parsingMode = ParsingMode::headerValue;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData1.append(previous, (current - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::headerValue:
            while (current < end)
            {
                if (*current == ' ')
                {
                    ++current;
                }
                else
                {
                    break;
                }
            }
            previous = current;
            while (current < end)
            {
                if (*current == '\r')
                {
                    if (m_fragmentedData1.empty() && m_fragmentedData2.empty())
                    {
                        boost::string_view headerName(headerNameBegin, (headerNameEnd - headerNameBegin));
                        boost::string_view headerValue(previous, (current - previous));
                        if (headerName == "Content-Length")
                        {
                            // TODO: I actually want to use errors because we could be received lots of invalid
                            // messages from misbehaved clients
                            Error error;
                            size_t contentLength = 0;
                            ASCII::Convert(headerValue.begin(), headerValue.end(), contentLength, error);
                            // TODO: handle error
                            m_remainingContentLength = contentLength;
                        }
                        m_callbacks.onHeader(headerName, headerValue);
                    }
                    else if (!m_fragmentedData1.empty() && m_fragmentedData2.empty())
                    {
                        boost::string_view headerValue(previous, (current - previous));
                        if (m_fragmentedData1 == "Content-Length")
                        {
                            // TODO: I actually want to use errors because we could be received lots of invalid
                            // messages from misbehaved clients
                            Error error;
                            size_t contentLength = 0;
                            ASCII::Convert(headerValue.begin(), headerValue.end(), contentLength, error);
                            // TODO: handle error
                            m_remainingContentLength = contentLength;
                        }
                        m_callbacks.onHeader(m_fragmentedData1, headerValue);
                        m_fragmentedData1.clear();
                    }
                    else
                    {
                        m_fragmentedData2.append(data.data(), current - data.data());
                        if (m_fragmentedData1 == "Content-Length")
                        {
                            // TODO: I actually want to use errors because we could be received lots of invalid
                            // messages from misbehaved clients
                            Error error;
                            size_t contentLength = 0;
                            ASCII::Convert(m_fragmentedData2.begin(), m_fragmentedData2.end(), contentLength, error);
                            // TODO: handle error
                            m_remainingContentLength = contentLength;
                        }
                        m_callbacks.onHeader(m_fragmentedData1, m_fragmentedData2);
                        m_fragmentedData1.clear();
                        m_fragmentedData2.clear();
                    }
                    
                    notifyHeader();
                }
                else if (*current == '\n')
                {
                    m_parsingMode = ParsingMode::headerOrSeparator;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                // TODO: handle case where data size is 0
                const char* adjustedCurrent = current;
                if (*(current - 1) == '\r')
                {
                    --adjustedCurrent;
                }
                m_fragmentedData2.append(previous, (adjustedCurrent - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::separator:
            if ((current != end) && (*current == '\n'))
            {
                ++current;
                if (current < end)
                {
                    m_parsingMode = ParsingMode::body;
                }
                else
                {
                    return true;
                }
            }
            else
            {
                // TODO: error
                ++current;
            }
            break;

        case ParsingMode::body:
            if (m_remainingContentLength && (*m_remainingContentLength > 0))
            {
                // TODO: this is very problematic. The presence of a body may depend on the request the response is
                // associated with e.g. HEAD. This means there is no point in having this generic parser. I may as well
                // split into Request and Response parser and the response parser needs to have some info about which
                // request it is associated with.
                // TODO: take into account Content-Length
                m_callbacks.onBodyFragment(boost::string_view(current, (end - current)));
            }
            return true;
        }

        // TODO: add an end state and error if trying to push more data
    }
    return false;
}

void HTTPResponsePushParser::notifyHeader()
{
    /*
    if (strncmp(m_headerName, "Accept", 7) == 0)
    {
        m_accept = m_headerValue;
        while ((*m_accept == ' ') || (*m_accept == '\t'))
        {
            ++m_accept;
        }
    }
    else if (strncmp(m_parsingState.m_headerName, "Accept-Charset", 15) == 0)
    {
        m_acceptCharset = m_headerValue;
        while ((*m_acceptCharset == ' ') || (*m_acceptCharset == '\t'))
        {
            ++m_acceptCharset;
        }
    }
    else if (strncmp(m_parsingState.m_headerName, "Accept-Encoding", 16) == 0)
    {
        m_acceptEncoding = m_headerValue;
        while ((*m_acceptEncoding == ' ') || (*m_acceptEncoding == '\t'))
        {
            ++m_acceptEncoding;
        }
    }
    else if (strncmp(m_parsingState.m_headerName, "Accept-Language", 16) == 0)
    {
        m_acceptLanguage = m_headerValue;
        while ((*m_acceptLanguage == ' ') || (*m_acceptLanguage == '\t'))
        {
            ++m_acceptLanguage;
        }
    }
    else if (strncmp(m_parsingState.m_headerName, "Content-Length", 15) == 0)
    {
        m_contentLength = m_headerValue;
        while ((*m_contentLength == ' ') || (*m_contentLength == '\t'))
        {
            ++m_contentLength;
        }
    }
    else if (strncmp(m_parsingState.m_headerName, "Host", 5) == 0)
    {
        m_host = m_headerValue;
        while ((*m_host == ' ') || (*m_host == '\t'))
        {
            ++m_host;
        }
    }
    else if (strncmp(m_parsingState.m_headerName, "Transfer-Encoding", 18) == 0)
    {
        m_transferEncoding = m_headerValue;
        while ((*m_transferEncoding == ' ') || (*m_transferEncoding == '\t'))
        {
            ++m_transferEncoding;
        }
    }*/
}
