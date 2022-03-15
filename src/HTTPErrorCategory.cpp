/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPErrorCategory.hpp"

namespace Ishiko
{

const HTTPErrorCategory& HTTPErrorCategory::Get() noexcept
{
    static HTTPErrorCategory theCategory;
    return theCategory;
}

const char* HTTPErrorCategory::name() const noexcept
{
    return "Ishiko::HTTPErrorCategory";
}

void Fail(Error& error, HTTPErrorCategory::Value value, const std::string& message, const char* file, int line) noexcept
{
    error.fail(static_cast<int>(value), HTTPErrorCategory::Get(), message, file, line);
}

}
