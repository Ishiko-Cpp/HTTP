/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPClientTests.hpp"
#include "HTTPMessagePushParserTests.hpp"
#include "HTTPRequestTests.hpp"
#include "Ishiko/HTTP/linkoptions.hpp"
#include <Ishiko/Tests.hpp>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoHTTP");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<HTTPRequestTests>();
    theTests.append<HTTPMessagePushParserTests>();
    theTests.append<HTTPClientTests>();

    return theTestHarness.run();
}
