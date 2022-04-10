/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPREQUESTTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPREQUESTTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class HTTPRequestTests : public Ishiko::TestSequence
{
public:
    HTTPRequestTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ToStringTest1(Ishiko::FileComparisonTest& test);
};

#endif
