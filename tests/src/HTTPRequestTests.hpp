/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_HTTP_TESTS_HTTPREQUESTTESTS_HPP_
#define _ISHIKO_HTTP_TESTS_HTTPREQUESTTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class HTTPRequestTests : public Ishiko::Tests::TestSequence
{
public:
    HTTPRequestTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ToStringTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif
