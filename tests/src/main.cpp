/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPClientTests.hpp"
#include "HTTPMessagePushParserTests.hpp"
#include "HTTPRequestTests.hpp"
#include "HTTPResponseTests.hpp"
#include "Ishiko/HTTP/linkoptions.hpp"
#include <Ishiko/Tests.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoHTTP");

    theTestHarness.context().setTestDataDirectory("../../data");
    theTestHarness.context().setTestOutputDirectory("../../output");
    theTestHarness.context().setReferenceDataDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<HTTPRequestTests>();
    theTests.append<HTTPResponseTests>();
    theTests.append<HTTPMessagePushParserTests>();
    theTests.append<HTTPClientTests>();

    return theTestHarness.run();
}
