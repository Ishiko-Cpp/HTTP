/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_HTTPERRORCATEGORY_HPP_
#define _ISHIKO_CPP_HTTP_HTTPERRORCATEGORY_HPP_

#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class HTTPErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum class Value
    {
        generic = -1
    };

    static const HTTPErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    HTTPErrorCategory() noexcept = default;
};

void Fail(Error& error, HTTPErrorCategory::Value value, const std::string& message, const char* file, int line) noexcept;

}

#endif
