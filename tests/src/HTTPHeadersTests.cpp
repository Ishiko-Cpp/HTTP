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
    append<HeapAllocationErrorsTest>("push_back test 1", PushBackTest1);
    append<HeapAllocationErrorsTest>("push_back test 2", PushBackTest2);
    append<HeapAllocationErrorsTest>("push_back test 3", PushBackTest3);
}

void HTTPHeadersTests::ConstructorTest1(Test& test)
{
    HTTPHeaders headers;

    ISHIKO_TEST_FAIL_IF_NEQ(headers.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(headers.begin(), headers.end());
    ISHIKO_TEST_PASS();
}

void HTTPHeadersTests::PushBackTest1(Test& test)
{
    HTTPHeaders headers;

    headers.push_back(HTTPHeader("name", "value"));

    ISHIKO_TEST_FAIL_IF_NEQ(headers.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(headers.at("name").value(), "value");
    ISHIKO_TEST_FAIL_IF_NEQ((headers.begin() + 1), headers.end());
    ISHIKO_TEST_FAIL_IF_NEQ(headers.begin()->name(), "name");
    ISHIKO_TEST_FAIL_IF_NEQ(headers.begin()->value(), "value");
    ISHIKO_TEST_PASS();
}

void HTTPHeadersTests::PushBackTest2(Test& test)
{
    HTTPHeaders headers;

    headers.push_back(HTTPHeader("name1", "value1"));
    headers.push_back(HTTPHeader("name2", "value2"));

    ISHIKO_TEST_FAIL_IF_NEQ(headers.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(headers.at("name1").value(), "value1");
    ISHIKO_TEST_FAIL_IF_NEQ(headers.at("name2").value(), "value2");
    ISHIKO_TEST_FAIL_IF_NEQ((headers.begin() + 2), headers.end());

    HTTPHeaders::const_iterator it = headers.begin();

    ISHIKO_TEST_FAIL_IF_NEQ(it->name(), "name1");
    ISHIKO_TEST_FAIL_IF_NEQ(it->value(), "value1");

    ++it;

    ISHIKO_TEST_FAIL_IF_NEQ(it->name(), "name2");
    ISHIKO_TEST_FAIL_IF_NEQ(it->value(), "value2");

    ISHIKO_TEST_PASS();
}

void HTTPHeadersTests::PushBackTest3(Test& test)
{
    HTTPHeaders headers;

    headers.push_back("name", "value");

    ISHIKO_TEST_FAIL_IF_NEQ(headers.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(headers.at("name").value(), "value");
    ISHIKO_TEST_FAIL_IF_NEQ((headers.begin() + 1), headers.end());
    ISHIKO_TEST_FAIL_IF_NEQ(headers.begin()->name(), "name");
    ISHIKO_TEST_FAIL_IF_NEQ(headers.begin()->value(), "value");
    ISHIKO_TEST_PASS();
}
