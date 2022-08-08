/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPErrorCategory.hpp"

using namespace Ishiko;

const HTTPErrorCategory& HTTPErrorCategory::Get() noexcept
{
    static HTTPErrorCategory theCategory;
    return theCategory;
}

const char* HTTPErrorCategory::name() const noexcept
{
    return "Ishiko::HTTPErrorCategory";
}

void Ishiko::Fail(HTTPErrorCategory::Value value, const std::string& message, const char* file, int line,
    Error& error) noexcept
{
    error.fail(HTTPErrorCategory::Get(), static_cast<int>(value), message, file, line);
}
