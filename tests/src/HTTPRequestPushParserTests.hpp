/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPREQUESTPUSHPARSERTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPREQUESTPUSHPARSERTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class HTTPRequestPushParserTests : public Ishiko::TestSequence
{
public:
    HTTPRequestPushParserTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

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
