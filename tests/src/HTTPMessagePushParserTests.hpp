/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_HTTP_TESTS_HTTPMESSAGEPUSHPARSERTESTS_HPP_
#define _ISHIKO_HTTP_TESTS_HTTPMESSAGEPUSHPARSERTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class HTTPMessagePushParserTests : public Ishiko::Tests::TestSequence
{
public:
    HTTPMessagePushParserTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void OnDataTest1(Ishiko::Tests::Test& test);
};

#endif
