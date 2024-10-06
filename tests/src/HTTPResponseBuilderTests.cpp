// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "HTTPResponseBuilderTests.hpp"
#include "Ishiko/HTTP/HTTPResponseBuilder.hpp"

using namespace Ishiko;

HTTPResponseBuilderTests::HTTPResponseBuilderTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPResponseBuilder tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void HTTPResponseBuilderTests::ConstructorTest1(Test& test)
{
    HTTPResponseBuilder response_builder;

    ISHIKO_TEST_PASS();
}
