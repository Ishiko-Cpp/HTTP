/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPMessagePushParserTests.hpp"
#include "Ishiko/HTTP/HTTPMessagePushParser.hpp"

using namespace Ishiko;
using namespace Ishiko::Tests;

HTTPMessagePushParserTests::HTTPMessagePushParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPMessagePushParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void HTTPMessagePushParserTests::ConstructorTest1(Test& test)
{
    HTTPMessagePushParser::Callbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
     
    ISHIKO_PASS();
}
