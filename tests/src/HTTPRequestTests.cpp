/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPRequestTests.hpp"
#include "Ishiko/HTTP/HTTPRequest.hpp"

using namespace Ishiko;
using namespace Ishiko::Tests;

HTTPRequestTests::HTTPRequestTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPRequest tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void HTTPRequestTests::ConstructorTest1(Test& test)
{
    HTTPRequest request;

    ISHIKO_PASS();
}
