/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPResponsePushParserTests.hpp"
#include "helpers/HTTPResponsePushParserTestCallbacks.hpp"
#include "Ishiko/HTTP/HTTPResponsePushParser.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/FileSystem.hpp>
#include <string>

using namespace Ishiko;

HTTPResponsePushParserTests::HTTPResponsePushParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPResponsePushParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("onData test 1", OnDataTest1);
    append<HeapAllocationErrorsTest>("onData test 2", OnDataTest2);
    append<HeapAllocationErrorsTest>("onData test 3", OnDataTest3);
}

void HTTPResponsePushParserTests::ConstructorTest1(Test& test)
{
    HTTPResponsePushParser::Callbacks callbacks;
    HTTPResponsePushParser parser(callbacks);
     
    ISHIKO_TEST_PASS();
}

void HTTPResponsePushParserTests::OnDataTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPResponsePushParserTests_OnDataTest1.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPResponsePushParserTestCallbacks callbacks;
    HTTPResponsePushParser parser(callbacks);
    bool complete = parser.onData(message);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.statusCode(), "200");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.reasonPhrase(), "OK");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers().size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.body(), "");
    ISHIKO_TEST_PASS();
}

void HTTPResponsePushParserTests::OnDataTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPResponsePushParserTests_OnDataTest2.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPResponsePushParserTestCallbacks callbacks;
    HTTPResponsePushParser parser(callbacks);
    bool complete = parser.onData(message);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.statusCode(), "200");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.reasonPhrase(), "OK");
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.headers().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].first, "Content-Length");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].second, "0");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.body(), "");
    ISHIKO_TEST_PASS();
}

void HTTPResponsePushParserTests::OnDataTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("HTTPResponsePushParserTests_OnDataTest3.bin");

    Error error;
    std::string message = FileSystem::ReadFile(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    HTTPResponsePushParserTestCallbacks callbacks;
    HTTPResponsePushParser parser(callbacks);
    bool complete = parser.onData(message);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.httpVersion(), "HTTP/1.1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.statusCode(), "200");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.reasonPhrase(), "OK");
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.headers().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].first, "Content-Length");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.headers()[0].second, "4");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.body(), "body");
    ISHIKO_TEST_PASS();
}
