// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_HTTP_HTTPHEADER_HPP
#define GUARD_ISHIKO_CPP_HTTP_HTTPHEADER_HPP

#include <Ishiko/Time.hpp>
#include <Ishiko/Types.hpp>
#include <string>

namespace Ishiko
{
    class HTTPHeader
    {
    public:
        enum class ConnectionMode
        {
            close,
            keepAlive
        };

        HTTPHeader(std::string name, std::string value);
        static HTTPHeader Connection(ConnectionMode mode);
        static HTTPHeader Date(const UTCTime& time);
        static HTTPHeader Host(const std::string& host);
        static HTTPHeader Location(const URL& locationn);

        const std::string& name() const;
        const std::string& value() const;
        void setValue(const std::string& value);

        std::string toString() const;

    private:
        std::string m_name;
        std::string m_value;
    };
}

#endif
