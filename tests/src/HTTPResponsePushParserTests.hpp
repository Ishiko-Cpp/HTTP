/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSEPUSHPARSERTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSEPUSHPARSERTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class HTTPResponsePushParserTests : public Ishiko::TestSequence
{
public:
    HTTPResponsePushParserTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void OnDataTest1(Ishiko::Test& test);
    static void OnDataTest2(Ishiko::Test& test);
    static void OnDataTest3(Ishiko::Test& test);
};

#endif
