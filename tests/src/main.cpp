/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPClientTests.hpp"
#include "HTTPHeaderTests.hpp"
#include "HTTPHeadersTests.hpp"
#include "HTTPRequestPushParserTests.hpp"
#include "HTTPRequestTests.hpp"
#include "HTTPResponseTests.hpp"
#include "HTTPResponsePushParserTests.hpp"
#include "HTTPSClientTests.hpp"
#include "Ishiko/HTTP/linkoptions.hpp"
#include <Ishiko/TestFramework.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoHTTP");

    theTestHarness.context().setTestDataDirectory("../../data");
    theTestHarness.context().setTestOutputDirectory("../../output");
    theTestHarness.context().setReferenceDataDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<HTTPRequestPushParserTests>();
    theTests.append<HTTPResponsePushParserTests>();
    theTests.append<HTTPHeaderTests>();
    theTests.append<HTTPHeadersTests>();
    theTests.append<HTTPRequestTests>();
    theTests.append<HTTPResponseTests>();
    theTests.append<HTTPClientTests>();
    theTests.append<HTTPSClientTests>();

    return theTestHarness.run();
}
