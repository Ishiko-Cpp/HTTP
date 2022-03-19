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
    append<HeapAllocationErrorsTest>("Date test 1", DateTest1);
}

void HTTPHeaderTests::ConstructorTest1(Test& test)
{
    HTTPHeader header("name", "value");

    ISHIKO_TEST_FAIL_IF_NEQ(header.name(), "name");
    ISHIKO_TEST_FAIL_IF_NEQ(header.value(), "value");
    ISHIKO_TEST_PASS();
}

void HTTPHeaderTests::DateTest1(Test& test)
{
    HTTPHeader header = HTTPHeader::Date(TimePoint(Date(2022, 3, 19), TimeOfDay(19, 56, 02)));

    ISHIKO_TEST_FAIL_IF_NEQ(header.name(), "Date");
    ISHIKO_TEST_FAIL_IF_NEQ(header.value(), "Sat, 19 Mar 2022 19:56:02 GMT");
    ISHIKO_TEST_PASS();
}
