/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPCLIENTTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPCLIENTTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class HTTPClientTests : public Ishiko::TestSequence
{
public:
    HTTPClientTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void GetTest1(Ishiko::Test& test);
    static void GetTest2(Ishiko::Test& test);
    static void GetTest3(Ishiko::Test& test);
    static void GetTest4(Ishiko::Test& test);
};

#endif
