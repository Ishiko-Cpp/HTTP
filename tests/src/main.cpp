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
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        TestHarness::CommandLineSpecification commandLineSpec;
        commandLineSpec.setDefaultValue("context.data", "../../data");
        commandLineSpec.setDefaultValue("context.output", "../../output");
        commandLineSpec.setDefaultValue("context.reference", "../../reference");

        Configuration configuration = commandLineSpec.createDefaultConfiguration();
        CommandLineParser::parse(commandLineSpec, argc, argv, configuration);

        TestHarness theTestHarness("Ishiko/C++ HTTP Library Tests", configuration);

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
    catch (const std::exception& e)
    {
        return TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return TestApplicationReturnCode::exception;
    }
}
