/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPHEADERTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPHEADERTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class HTTPHeaderTests : public Ishiko::TestSequence
{
public:
    HTTPHeaderTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void DateTest1(Ishiko::Test& test);
};

#endif
