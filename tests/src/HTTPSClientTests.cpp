/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPSClientTests.hpp"
#include "Ishiko/HTTP/HTTPSClient.hpp"

using namespace Ishiko;

HTTPSClientTests::HTTPSClientTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPSClient tests", context)
{
    append<HeapAllocationErrorsTest>("Get test 1", GetTest1);
}

// TODO: memory leak detected but is it real or due to Botan?
void HTTPSClientTests::GetTest1(Test& test)
{
    Error error;

    IPv4Address address = IPv4Address("188.114.97.0", error);

    ISHIKO_TEST_FAIL_IF(error);

    HTTPResponse response(HTTPStatusCode::ok);
    // TODO: use proper test website
    // TODO: defeine Port::https
    HTTPSClient::Get(address, 443, "https://www.ishiko.org", response, error);

    ISHIKO_TEST_FAIL_IF_NEQ(response.statusCode(), 200);
    ISHIKO_TEST_FAIL_IF_NEQ(response.headers().size(), 9);
    ISHIKO_TEST_FAIL_IF_NEQ(response.headers().at("Connection").value(), "close");
    ISHIKO_TEST_PASS();
}
