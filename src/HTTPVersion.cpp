/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPVersion.hpp"

using namespace std;

namespace Ishiko
{

string HTTPVersion::toString() const
{
    return "HTTP/1.1";
}

}
