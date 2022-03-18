/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPMessagePushParserTests.hpp"
#include "helpers/HTTPMessagePushParserTestCallbacks.hpp"
#include "Ishiko/HTTP/HTTPMessagePushParser.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/FileSystem.hpp>
#include <string>

using namespace boost;
using namespace boost::filesystem;
using namespace Ishiko;
using namespace Ishiko::Tests;
using namespace std;

HTTPMessagePushParserTests::HTTPMessagePushParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPMessagePushParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("onData test 1", OnDataTest1);
    append<HeapAllocationErrorsTest>("onData test 2", OnDataTest2);
    append<HeapAllocationErrorsTest>("onData test 3", OnDataTest3);
    append<HeapAllocationErrorsTest>("onData test 4", OnDataTest4);
    append<HeapAllocationErrorsTest>("onData test 5", OnDataTest5);
    append<HeapAllocationErrorsTest>("onData test 6", OnDataTest6);
}

void HTTPMessagePushParserTests::ConstructorTest1(Test& test)
{
    HTTPMessagePushParser::Callbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
     
    ISHIKO_TEST_PASS();
}

void HTTPMessagePushParserTests::OnDataTest1(Test& test)
{
    path inputPath(test.context().getTestDataPath("HTTPMessagePushParserTests_OnDataTest1.bin"));

    Error error;
    string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPMessagePushParserTestCallbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
    bool complete = parser.onData(message);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers().size(), 0);
    ISHIKO_TEST_PASS();
}

void HTTPMessagePushParserTests::OnDataTest2(Test& test)
{
    path inputPath(test.context().getTestDataPath("HTTPMessagePushParserTests_OnDataTest2.bin"));

    Error error;
    string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPMessagePushParserTestCallbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
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

void HTTPMessagePushParserTests::OnDataTest3(Test& test)
{
    path inputPath(test.context().getTestDataPath("HTTPMessagePushParserTests_OnDataTest3.bin"));

    Error error;
    string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPMessagePushParserTestCallbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
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

void HTTPMessagePushParserTests::OnDataTest4(Test& test)
{
    path inputPath(test.context().getTestDataPath("HTTPMessagePushParserTests_OnDataTest1.bin"));

    Error error;
    string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPMessagePushParserTestCallbacks callbacks;
    HTTPMessagePushParser parser(callbacks);

    // Feed the message byte per byte to test correct behaviour when the message is fragmented across multiple packets
    for (size_t i = 0; i < message.size(); ++i)
    {
        parser.onData(string_view(&message[i], 1));
    }

    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers().size(), 0);
    ISHIKO_TEST_PASS();
}

void HTTPMessagePushParserTests::OnDataTest5(Test& test)
{
    path inputPath(test.context().getTestDataPath("HTTPMessagePushParserTests_OnDataTest2.bin"));

    Error error;
    string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPMessagePushParserTestCallbacks callbacks;
    HTTPMessagePushParser parser(callbacks);

    // Feed the message byte per byte to test correct behaviour when the message is fragmented across multiple packets
    for (size_t i = 0; i < message.size(); ++i)
    {
        parser.onData(string_view(&message[i], 1));
    }

    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.headers().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].first, "Host");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].second, "example.org");
    ISHIKO_TEST_PASS();
}

void HTTPMessagePushParserTests::OnDataTest6(Test& test)
{
    path inputPath(test.context().getTestDataPath("HTTPMessagePushParserTests_OnDataTest3.bin"));

    Error error;
    string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPMessagePushParserTestCallbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
    
    // Feed the message byte per byte to test correct behaviour when the message is fragmented across multiple packets
    for (size_t i = 0; i < message.size(); ++i)
    {
        parser.onData(string_view(&message[i], 1));
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
