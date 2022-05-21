/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPSClientTests.hpp"
#include "Ishiko/HTTP/HTTPSClient.hpp"

using namespace Ishiko;

HTTPSClientTests::HTTPSClientTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPSClient tests", context)
{
    append<HeapAllocationErrorsTest>("Get test 1", GetTest1);
}

void HTTPSClientTests::GetTest1(Test& test)
{
    Error error;

    IPv4Address address = IPv4Address("104.21.31.121", error);

    ISHIKO_TEST_FAIL_IF(error);

    HTTPResponse response(HTTPStatusCode::ok);
    // TODO: use proper test website
    // TODO: defeine Port::https
    HTTPSClient::Get(address, 443, "https://needfulsoftware.com", response, error);

    ISHIKO_TEST_FAIL_IF_NEQ(response.statusCode(), 301);
    ISHIKO_TEST_FAIL_IF_NEQ(response.headers().size(), 11);
    //ISHIKO_TEST_FAIL_IF_NEQ(response.headers().at("Connection").value(), "close");
    //ISHIKO_TEST_FAIL_IF_NEQ(response.headers().at("Location").value(), "https://needfulsoftware.com/");
    ISHIKO_TEST_PASS();
}
