/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "HTTPRequestTests.hpp"
#include "Ishiko/HTTP/HTTPRequest.hpp"
#include <Ishiko/FileSystem.hpp>
#include <string>

using namespace boost::filesystem;
using namespace Ishiko;
using namespace Ishiko::Tests;
using namespace std;

HTTPRequestTests::HTTPRequestTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPRequest tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<FileComparisonTest>("toString test 1", ToStringTest1);
}

void HTTPRequestTests::ConstructorTest1(Test& test)
{
    HTTPRequest request(HTTPMethod::get, URL("http://example.org"));

    ISHIKO_TEST_FAIL_IF_NEQ(request.method(), HTTPMethod::get);
    ISHIKO_TEST_FAIL_IF_NEQ(request.requestURI(), "http://example.org");
    ISHIKO_TEST_PASS();
}

void HTTPRequestTests::ToStringTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputPath("HTTPRequestTests_ToStringTest1.bin"));

    HTTPRequest request(HTTPMethod::get, URL("http://example.org"));
    string requestString = request.toString();

    Error error;
    // TODO: should just throw an exception
    BinaryFile file = BinaryFile::Create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    file.write(requestString.c_str(), requestString.length());

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataPath("HTTPRequestTests_ToStringTest1.bin"));

    ISHIKO_TEST_PASS();
}
