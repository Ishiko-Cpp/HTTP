/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPMESSAGEPUSHPARSERTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPMESSAGEPUSHPARSERTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class HTTPMessagePushParserTests : public Ishiko::TestSequence
{
public:
    HTTPMessagePushParserTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void OnDataRequestTest1(Ishiko::Test& test);
    static void OnDataRequestTest2(Ishiko::Test& test);
    static void OnDataRequestTest3(Ishiko::Test& test);
    static void OnDataRequestTest4(Ishiko::Test& test);
    static void OnDataRequestTest5(Ishiko::Test& test);
    static void OnDataRequestTest6(Ishiko::Test& test);
    static void OnDataResponseTest1(Ishiko::Test& test);
    static void OnDataResponseTest2(Ishiko::Test& test);
    static void OnDataResponseTest3(Ishiko::Test& test);
};

#endif
