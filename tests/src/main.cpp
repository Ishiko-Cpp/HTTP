/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "ClientTests.hpp"
#include "HTTPMessageParserTests.hpp"
#include "Ishiko/HTTP/linkoptions.hpp"
#include <Ishiko/Tests.hpp>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoHTTP");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<HTTPMessageParserTests>();
    theTests.append<ClientTests>();

    return theTestHarness.run();
}
