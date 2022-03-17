/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPResponseTests.hpp"
#include "Ishiko/HTTP/HTTPResponse.hpp"

using namespace Ishiko;
using namespace Ishiko::Tests;

HTTPResponseTests::HTTPResponseTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPResponse tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void HTTPResponseTests::ConstructorTest1(Test& test)
{
    HTTPResponse response;

    ISHIKO_PASS();
}
