/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_CPP_HTTP_TESTS_HTTPCLIENTTESTS_HPP_
#define _ISHIKO_CPP_HTTP_TESTS_HTTPCLIENTTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class HTTPClientTests : public Ishiko::Tests::TestSequence
{
public:
    HTTPClientTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void GetTest1(Ishiko::Tests::Test& test);
};

#endif
