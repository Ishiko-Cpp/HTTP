/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "ClientTests.hpp"
#include "Ishiko/HTTP/HTTPClient.h"
#include <sstream>

using namespace Ishiko;
using namespace Ishiko::HTTP;
using namespace Ishiko::Tests;
using namespace std;

ClientTests::ClientTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Client tests", context)
{
    append<HeapAllocationErrorsTest>("Get test 1", GetTest1);
}

void ClientTests::GetTest1(Test& test)
{
    Error error;

    stringstream response;
    // TODO: use proper test website
    HTTPClient::Get("188.114.97.0", 80, "http://needfulsoftware.com", response, error);

    ISHIKO_FAIL_IF_NEQ(response.str().substr(0, 24), "HTTP/1.1 400 Bad Request");
    ISHIKO_PASS();
}
