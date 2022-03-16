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
}

void HTTPMessagePushParserTests::ConstructorTest1(Test& test)
{
    HTTPMessagePushParser::Callbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
     
    ISHIKO_PASS();
}

void HTTPMessagePushParserTests::OnDataTest1(Test& test)
{
    path inputPath(test.context().getTestDataPath("HTTPMessagePushParserTests_OnDataTest1.bin"));

    Error error;
    string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_ABORT_IF(error);

    HTTPMessagePushParserTestCallbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
    parser.onData(message);

    ISHIKO_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_FAIL_IF_NEQ(callbacks.headers().size(), 0);
    ISHIKO_PASS();
}

void HTTPMessagePushParserTests::OnDataTest2(Test& test)
{
    path inputPath(test.context().getTestDataPath("HTTPMessagePushParserTests_OnDataTest2.bin"));

    Error error;
    string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_ABORT_IF(error);

    HTTPMessagePushParserTestCallbacks callbacks;
    HTTPMessagePushParser parser(callbacks);
    parser.onData(message);

    ISHIKO_FAIL_IF_NEQ(callbacks.method(), "GET");
    ISHIKO_FAIL_IF_NEQ(callbacks.requestURI(), "/");
    ISHIKO_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_ABORT_IF_NEQ(callbacks.headers().size(), 1);
    ISHIKO_FAIL_IF_NEQ(callbacks.headers()[0].first, "Host");
    ISHIKO_FAIL_IF_NEQ(callbacks.headers()[0].second, "example.org");
    ISHIKO_PASS();
}
