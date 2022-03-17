/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSETESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSETESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class HTTPResponseTests : public Ishiko::Tests::TestSequence
{
public:
    HTTPResponseTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ToStringTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif
