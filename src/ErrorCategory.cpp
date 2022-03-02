/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "ErrorCategory.hpp"

namespace Ishiko
{
namespace HTTP
{

const ErrorCategory& ErrorCategory::Get() noexcept
{
    static ErrorCategory theCategory;
    return theCategory;
}

const char* ErrorCategory::name() const noexcept
{
    return "Ishiko::HTTP::ErrorCategory";
}

void Fail(Error& error, ErrorCategory::EErrorValues value, const std::string& message, const char* file,
    int line) noexcept
{
    error.fail(value, ErrorCategory::Get(), message, file, line);
}

}
}
