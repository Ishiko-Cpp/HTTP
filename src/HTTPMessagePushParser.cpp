/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPMessagePushParser.hpp"

using namespace boost;

namespace Ishiko
{

void HTTPMessagePushParser::Callbacks::onMethod(string_view data)
{
}

void HTTPMessagePushParser::Callbacks::onRequestURI(boost::string_view data)
{
}

void HTTPMessagePushParser::Callbacks::onHTTPVersion(boost::string_view data)
{
}

void HTTPMessagePushParser::Callbacks::onHeader(boost::string_view name, boost::string_view value)
{
}

void HTTPMessagePushParser::Callbacks::onBody(boost::string_view data)
{
}

HTTPMessagePushParser::HTTPMessagePushParser(Callbacks& callbacks)
    : m_callbacks(callbacks)
{
}

void HTTPMessagePushParser::onData(string_view data)
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
        case ParsingMode::method:
            while (current < end)
            {
                if (*current == ' ')
                {
                    if (m_fragmentedData1.empty())
                    {
                        m_callbacks.onMethod(string_view(previous, (current - previous)));
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
                        m_callbacks.onRequestURI(string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData1.append(data.data(), current - data.data());
                        m_callbacks.onRequestURI(m_fragmentedData1);
                        m_fragmentedData1.clear();
                    }
                    m_parsingMode = ParsingMode::httpVersion;
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

        case ParsingMode::httpVersion:
            previous = current;
            while (current < end)
            {
                if (*current == '\r')
                {
                    if (m_fragmentedData1.empty())
                    {
                        m_callbacks.onHTTPVersion(string_view(previous, (current - previous)));
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
                    m_parsingMode = ParsingMode::headers;
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

        case ParsingMode::headers:
            if (*current == '\r')
            {
                m_parsingMode = ParsingMode::body;
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
                        m_callbacks.onHeader(string_view(headerNameBegin, (headerNameEnd - headerNameBegin)),
                            string_view(previous, (current - previous)));
                    }
                    else if (!m_fragmentedData1.empty() && m_fragmentedData2.empty())
                    {
                        m_callbacks.onHeader(m_fragmentedData1, string_view(previous, (current - previous)));
                        m_fragmentedData1.clear();
                    }
                    else
                    {
                        m_fragmentedData2.append(data.data(), current - data.data());
                        m_callbacks.onHeader(m_fragmentedData1, m_fragmentedData2);
                        m_fragmentedData1.clear();
                        m_fragmentedData2.clear();
                    }
                    
                    notifyHeader();
                }
                else if (*current == '\n')
                {
                    m_parsingMode = ParsingMode::headers;
                    ++current;
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData2.append(previous, (current - previous));
            }
            else
            {
                ++current;
            }
            break;

        case ParsingMode::body:
            while (current < end)
            {
                ++current;
            }
            break;
        }
    }
}

void HTTPMessagePushParser::notifyHeader()
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

}
