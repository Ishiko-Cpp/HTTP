// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_HTTP_HTTPRESPONSE_HPP
#define GUARD_ISHIKO_CPP_HTTP_HTTPRESPONSE_HPP

#include "HTTPHeader.hpp"
#include "HTTPHeaders.hpp"
#include "HTTPResponsePushParser.hpp"
#include "HTTPStatusCode.hpp"
#include "HTTPVersion.hpp"
#include <Ishiko/Time.hpp>
#include <Ishiko/Types.hpp>
#include <string>
#include <vector>

namespace Ishiko
{
    class HTTPResponse
    {
    public:
        class ParserCallbacks : public HTTPResponsePushParser::Callbacks
        {
        public:
            ParserCallbacks(HTTPResponse& response);

            void onStatusCode(boost::string_view data) override;
            void onReasonPhrase(boost::string_view data) override;
            void onHeader(boost::string_view name, boost::string_view value) override;
            // TODO: we need to  set the body!
            void onBodyFragment(boost::string_view data) override;

        private:
            HTTPResponse& m_response;
        };

        HTTPResponse(HTTPStatusCode statusCode);
        static HTTPResponse OK();
        static HTTPResponse MovedPermanently(const URL& newLocation);
        static HTTPResponse BadRequest();
        static HTTPResponse NotFound();
        static HTTPResponse InternalServerError();

        HTTPStatusCode statusCode() const;
        const HTTPHeaders& headers() const;

        void setStatusCode(HTTPStatusCode statusCode);

        void setContentLengthHeader(size_t length);
        void setDateHeader(const UTCTime& time);
        void setLocationHeader(const URL& newLocation);
        void appendHeader(const std::string& name, const std::string& value);

        void setBody(const std::string& body);

        // TODO: this is a naive way to create a response as it could be very large. Some form of streaming, especially of
        // the body is required but it'll do for now
        std::string toString() const;

    private:
        HTTPVersion m_version;
        HTTPStatusCode m_statusCode;
        HTTPHeaders m_headers;
        std::string m_body;
    };
}

#endif
