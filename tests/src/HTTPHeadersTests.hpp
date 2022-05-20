/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPHEADERSTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPHEADERSTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class HTTPHeadersTests : public Ishiko::TestSequence
{
public:
    HTTPHeadersTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void PushBackTest1(Ishiko::Test& test);
    static void PushBackTest2(Ishiko::Test& test);
    static void PushBackTest3(Ishiko::Test& test);
};

#endif
