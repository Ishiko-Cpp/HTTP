/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPRequestPushParserTests.hpp"
#include "helpers/HTTPRequestPushParserTestCallbacks.hpp"
#include "Ishiko/HTTP/HTTPRequestPushParser.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/FileSystem.hpp>
#include <string>

using namespace Ishiko;

HTTPRequestPushParserTests::HTTPRequestPushParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPRequestPushParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("onData test 1", OnDataTest1);
    append<HeapAllocationErrorsTest>("onData test 2", OnDataTest2);
    append<HeapAllocationErrorsTest>("onData test 3", OnDataTest3);
    append<HeapAllocationErrorsTest>("onData test 4", OnDataTest4);
    append<HeapAllocationErrorsTest>("onData test 5", OnDataTest5);
    append<HeapAllocationErrorsTest>("onData test 6", OnDataTest6);
}

void HTTPRequestPushParserTests::ConstructorTest1(Test& test)
{
    HTTPRequestPushParser::Callbacks callbacks;
    HTTPRequestPushParser parser(callbacks);
     
    ISHIKO_TEST_PASS();
}

void HTTPRequestPushParserTests::OnDataTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPRequestPushParserTests_OnDataTest1.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPRequestPushParserTestCallbacks callbacks;
    HTTPRequestPushParser parser(callbacks);
    bool complete = parser.onData(message);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers().size(), 0);
    ISHIKO_TEST_PASS();
}

void HTTPRequestPushParserTests::OnDataTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPRequestPushParserTests_OnDataTest2.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPRequestPushParserTestCallbacks callbacks;
    HTTPRequestPushParser parser(callbacks);
    bool complete = parser.onData(message);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.headers().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].first, "Host");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].second, "example.org");
    ISHIKO_TEST_PASS();
}

void HTTPRequestPushParserTests::OnDataTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPRequestPushParserTests_OnDataTest3.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPRequestPushParserTestCallbacks callbacks;
    HTTPRequestPushParser parser(callbacks);
    bool complete = parser.onData(message);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.headers().size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].first, "Host");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].second, "example.org");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[1].first, "Connection");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[1].second, "keep-alive");
    ISHIKO_TEST_PASS();
}

void HTTPRequestPushParserTests::OnDataTest4(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPRequestPushParserTests_OnDataTest1.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPRequestPushParserTestCallbacks callbacks;
    HTTPRequestPushParser parser(callbacks);

    // Feed the message byte per byte to test correct behaviour when the message is fragmented across multiple packets
    for (size_t i = 0; i < message.size(); ++i)
    {
        parser.onData(boost::string_view(&message[i], 1));
    }

    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers().size(), 0);
    ISHIKO_TEST_PASS();
}

void HTTPRequestPushParserTests::OnDataTest5(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPRequestPushParserTests_OnDataTest2.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPRequestPushParserTestCallbacks callbacks;
    HTTPRequestPushParser parser(callbacks);

    // Feed the message byte per byte to test correct behaviour when the message is fragmented across multiple packets
    for (size_t i = 0; i < message.size(); ++i)
    {
        parser.onData(boost::string_view(&message[i], 1));
    }

    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.headers().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].first, "Host");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].second, "example.org");
    ISHIKO_TEST_PASS();
}

void HTTPRequestPushParserTests::OnDataTest6(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPRequestPushParserTests_OnDataTest3.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPRequestPushParserTestCallbacks callbacks;
    HTTPRequestPushParser parser(callbacks);
    
    // Feed the message byte per byte to test correct behaviour when the message is fragmented across multiple packets
    for (size_t i = 0; i < message.size(); ++i)
    {
        parser.onData(boost::string_view(&message[i], 1));
    }

    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.headers().size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].first, "Host");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].second, "example.org");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[1].first, "Connection");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[1].second, "keep-alive");
    ISHIKO_TEST_PASS();
}
