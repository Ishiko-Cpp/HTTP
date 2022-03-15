/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPMessageParserTests.hpp"
#include "Ishiko/HTTP/HTTPMessageParser.hpp"

using namespace Ishiko;
using namespace Ishiko::Tests;

HTTPMessageParserTests::HTTPMessageParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPMessageParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void HTTPMessageParserTests::ConstructorTest1(Test& test)
{
    HTTPMessageParser parser;
     
    ISHIKO_PASS();
}
