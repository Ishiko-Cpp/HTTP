/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPHeadersTests.hpp"
#include "Ishiko/HTTP/HTTPHeaders.hpp"

using namespace Ishiko;

HTTPHeadersTests::HTTPHeadersTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPHeaders tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void HTTPHeadersTests::ConstructorTest1(Test& test)
{
    HTTPHeaders headers;

    ISHIKO_TEST_FAIL_IF_NEQ(headers.size(), 0);
    ISHIKO_TEST_PASS();
}
