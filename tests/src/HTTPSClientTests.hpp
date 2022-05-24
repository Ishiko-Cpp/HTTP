/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPSCLIENTTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPSCLIENTTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class HTTPSClientTests : public Ishiko::TestSequence
{
public:
    HTTPSClientTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void GetTest1(Ishiko::Test& test);
};

#endif
