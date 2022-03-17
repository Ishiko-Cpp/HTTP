/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPStatusCode.hpp"

using namespace std;

namespace Ishiko
{

HTTPStatusCode::HTTPStatusCode()
{
}

string HTTPStatusCode::getReasonPhrase() const
{
    return "OK";
}

string HTTPStatusCode::toString() const
{
    return "200";
}

}
