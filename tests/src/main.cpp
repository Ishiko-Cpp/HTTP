// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "HTTPClientTests.hpp"
#include "HTTPHeaderTests.hpp"
#include "HTTPHeadersTests.hpp"
#include "HTTPRequestPushParserTests.hpp"
#include "HTTPRequestTests.hpp"
#include "HTTPResponseBuilderTests.hpp"
#include "HTTPResponsePushParserTests.hpp"
#include "HTTPResponseTests.hpp"
#include "HTTPSClientTests.hpp"
#include "Ishiko/HTTP/linkoptions.hpp"
#include <Ishiko/Networking.hpp>
#include <Ishiko/TestFramework.hpp>
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        NetworkingLibraryInitialization network_library_initialization;

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
        theTests.append<HTTPResponseBuilderTests>();
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
