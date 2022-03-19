/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSETESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSETESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class HTTPResponseTests : public Ishiko::TestSequence
{
public:
    HTTPResponseTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void NotFoundTest1(Ishiko::Test& test);
    static void ToStringTest1(Ishiko::FileComparisonTest& test);
    static void ToStringTest2(Ishiko::FileComparisonTest& test);
};

#endif
