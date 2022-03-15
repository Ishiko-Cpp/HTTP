/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPMessagePushParserTests.hpp"
#include "Ishiko/HTTP/HTTPMessageParser.hpp"

using namespace Ishiko;
using namespace Ishiko::Tests;

HTTPMessagePushParserTests::HTTPMessagePushParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPMessagePushParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void HTTPMessagePushParserTests::ConstructorTest1(Test& test)
{
    HTTPMessagePushParser parser;
     
    ISHIKO_PASS();
}
