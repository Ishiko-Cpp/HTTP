/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPHeaderTests.hpp"
#include "Ishiko/HTTP/HTTPHeader.hpp"

using namespace Ishiko;

HTTPHeaderTests::HTTPHeaderTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPHeader tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void HTTPHeaderTests::ConstructorTest1(Test& test)
{
    HTTPHeader header("name", "value");

    ISHIKO_TEST_PASS();
}
