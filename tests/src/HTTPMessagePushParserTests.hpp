/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPMESSAGEPUSHPARSERTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPMESSAGEPUSHPARSERTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class HTTPMessagePushParserTests : public Ishiko::TestSequence
{
public:
    HTTPMessagePushParserTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void OnDataTest1(Ishiko::Test& test);
    static void OnDataTest2(Ishiko::Test& test);
    static void OnDataTest3(Ishiko::Test& test);
    static void OnDataTest4(Ishiko::Test& test);
    static void OnDataTest5(Ishiko::Test& test);
    static void OnDataTest6(Ishiko::Test& test);
};

#endif
