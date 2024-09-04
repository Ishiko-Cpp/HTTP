/*
    Copyright (c) 2022-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_HTTP_HTTPERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_HTTP_HTTPERRORCATEGORY_HPP

#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class HTTPErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum class Value
    {
        generic_error = -1
    };

    static const HTTPErrorCategory& Get() noexcept;

    const char* name() const noexcept override;
    const char* message(int ev, char* buffer, size_t len) const noexcept override;

private:
    HTTPErrorCategory() noexcept = default;
};

void Fail(HTTPErrorCategory::Value value, const std::string& message, const char* file, int line,
    Error& error) noexcept;

}

#endif
