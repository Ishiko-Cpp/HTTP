/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPRequestTests.hpp"
#include "Ishiko/HTTP/HTTPRequest.hpp"
#include <Ishiko/FileSystem.hpp>
#include <string>

using namespace Ishiko;

HTTPRequestTests::HTTPRequestTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPRequest tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("setConnectionHeader test 1", SetConnectionHeaderTest1);
    append<HeapAllocationErrorsTest>("setConnectionHeader test 2", SetConnectionHeaderTest2);
    append<HeapAllocationErrorsTest>("toString test 1", ToStringTest1);
    append<HeapAllocationErrorsTest>("toString test 2", ToStringTest2);
}

void HTTPRequestTests::ConstructorTest1(Test& test)
{
    HTTPRequest request(HTTPMethod::get, URL("http://example.org"));

    ISHIKO_TEST_FAIL_IF_NEQ(request.method(), HTTPMethod::get);
    ISHIKO_TEST_FAIL_IF_NEQ(request.requestURI(), "http://example.org");
    ISHIKO_TEST_ABORT_IF_NEQ(request.headers().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(request.headers().at("Host").value(), "example.org");
    ISHIKO_TEST_PASS();
}

void HTTPRequestTests::SetConnectionHeaderTest1(Ishiko::Test& test)
{
    HTTPRequest request(HTTPMethod::get, URL("http://example.org"));

    request.setConnectionHeader(HTTPHeader::ConnectionMode::close);

    ISHIKO_TEST_FAIL_IF_NEQ(request.headers().size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(request.headers().at("Host").value(), "example.org");
    ISHIKO_TEST_FAIL_IF_NEQ(request.headers().at("Connection").value(), "close");
    ISHIKO_TEST_PASS();
}

void HTTPRequestTests::SetConnectionHeaderTest2(Ishiko::Test& test)
{
    HTTPRequest request(HTTPMethod::get, URL("http://example.org"));

    request.setConnectionHeader(HTTPHeader::ConnectionMode::close);
    request.setConnectionHeader(HTTPHeader::ConnectionMode::keepAlive);

    ISHIKO_TEST_ABORT_IF_NEQ(request.headers().size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(request.headers().at("Host").value(), "example.org");
    ISHIKO_TEST_FAIL_IF_NEQ(request.headers().at("Connection").value(), "keep-alive");
    ISHIKO_TEST_PASS();
}

void HTTPRequestTests::ToStringTest1(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("HTTPRequestTests_ToStringTest1.bin");

    HTTPRequest request(HTTPMethod::get, URL("http://example.org"));
    std::string requestString = request.toString();

    Error error;
    // TODO: should just throw an exception
    BinaryFile file = BinaryFile::Create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    file.write(requestString.c_str(), requestString.length(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("HTTPRequestTests_ToStringTest1.bin");
    ISHIKO_TEST_PASS();
}

void HTTPRequestTests::ToStringTest2(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("HTTPRequestTests_ToStringTest2.bin");

    HTTPRequest request(HTTPMethod::get, URL("http://example.org"));
    request.setConnectionHeader(HTTPHeader::ConnectionMode::keepAlive);
    std::string requestString = request.toString();

    Error error;
    // TODO: should just throw an exception
    BinaryFile file = BinaryFile::Create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    file.write(requestString.c_str(), requestString.length(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("HTTPRequestTests_ToStringTest2.bin");
    ISHIKO_TEST_PASS();
}
