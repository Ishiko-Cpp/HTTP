/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPClientTests.hpp"
#include "Ishiko/HTTP/HTTPClient.hpp"
#include <sstream>

using namespace Ishiko;
using namespace std;

HTTPClientTests::HTTPClientTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Client tests", context)
{
    append<HeapAllocationErrorsTest>("Get test 1", GetTest1);
    append<HeapAllocationErrorsTest>("Get test 2", GetTest2);
}

void HTTPClientTests::GetTest1(Test& test)
{
    Error error;

    IPv4Address address = IPv4Address("188.114.97.0", error);

    ISHIKO_TEST_FAIL_IF(error);

    stringstream response;
    // TODO: use proper test website
    HTTPClient::Get(address, Port::http, "http://needfulsoftware.com", response, error);

    ISHIKO_TEST_FAIL_IF_NEQ(response.str().substr(0, 30), "HTTP/1.1 301 Moved Permanently");
    ISHIKO_TEST_PASS();
}


void HTTPClientTests::GetTest2(Test& test)
{
    Error error;

    stringstream response;
    // TODO: use proper test website
    HTTPClient::Get("188.114.97.0", 80, "http://needfulsoftware.com", response, error);

    ISHIKO_TEST_FAIL_IF_NEQ(response.str().substr(0, 30), "HTTP/1.1 301 Moved Permanently");
    ISHIKO_TEST_PASS();
}
