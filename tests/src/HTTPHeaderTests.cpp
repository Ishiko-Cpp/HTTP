/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPHeaderTests.hpp"
#include "Ishiko/HTTP/HTTPHeader.hpp"

using namespace Ishiko;

HTTPHeaderTests::HTTPHeaderTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPHeader tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Connection test 1", ConnectionTest1);
    append<HeapAllocationErrorsTest>("Connection test 2", ConnectionTest2);
    append<HeapAllocationErrorsTest>("Date test 1", DateTest1);
}

void HTTPHeaderTests::ConstructorTest1(Test& test)
{
    HTTPHeader header("name", "value");

    ISHIKO_TEST_FAIL_IF_NEQ(header.name(), "name");
    ISHIKO_TEST_FAIL_IF_NEQ(header.value(), "value");
    ISHIKO_TEST_PASS();
}

void HTTPHeaderTests::ConnectionTest1(Test& test)
{
    HTTPHeader header = HTTPHeader::Connection(HTTPHeader::ConnectionMode::close);

    ISHIKO_TEST_FAIL_IF_NEQ(header.name(), "Connection");
    ISHIKO_TEST_FAIL_IF_NEQ(header.value(), "close");
    ISHIKO_TEST_PASS();
}

void HTTPHeaderTests::ConnectionTest2(Test& test)
{
    HTTPHeader header = HTTPHeader::Connection(HTTPHeader::ConnectionMode::keep_alive);

    ISHIKO_TEST_FAIL_IF_NEQ(header.name(), "Connection");
    ISHIKO_TEST_FAIL_IF_NEQ(header.value(), "keep-alive");
    ISHIKO_TEST_PASS();
}

void HTTPHeaderTests::DateTest1(Test& test)
{
    HTTPHeader header = HTTPHeader::Date(UTCTime(Date(2022, 3, 19), TimeOfDay(19, 56, 02)));

    ISHIKO_TEST_FAIL_IF_NEQ(header.name(), "Date");
    ISHIKO_TEST_FAIL_IF_NEQ(header.value(), "Sat, 19 Mar 2022 19:56:02 GMT");
    ISHIKO_TEST_PASS();
}
