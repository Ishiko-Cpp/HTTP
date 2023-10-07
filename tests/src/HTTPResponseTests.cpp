/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPResponseTests.hpp"
#include "Ishiko/HTTP/HTTPResponse.hpp"
#include <Ishiko/FileSystem.hpp>

using namespace Ishiko;

HTTPResponseTests::HTTPResponseTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HTTPResponse tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("NotFound test 1", NotFoundTest1);
    append<HeapAllocationErrorsTest>("toString test 1", ToStringTest1);
    append<HeapAllocationErrorsTest>("toString test 2", ToStringTest2);
}

void HTTPResponseTests::ConstructorTest1(Test& test)
{
    HTTPResponse response(HTTPStatusCode::ok);

    ISHIKO_TEST_FAIL_IF_NEQ(response.statusCode(), 200);
    ISHIKO_TEST_PASS();
}

void HTTPResponseTests::NotFoundTest1(Test& test)
{
    HTTPResponse response = HTTPResponse::NotFound();

    ISHIKO_TEST_FAIL_IF_NEQ(response.statusCode(), 404);
    ISHIKO_TEST_PASS();
}

void HTTPResponseTests::ToStringTest1(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("HTTPResponseTests_ToStringTest1.bin");

    HTTPResponse response(HTTPStatusCode::ok);
    std::string responseString = response.toString();

    Error error;
    // TODO: should just throw an exception
    BinaryFile file = BinaryFile::Create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    file.write(responseString.c_str(), responseString.length(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("HTTPResponseTests_ToStringTest1.bin");
    ISHIKO_TEST_PASS();
}

void HTTPResponseTests::ToStringTest2(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("HTTPResponseTests_ToStringTest2.bin");

    HTTPResponse response(HTTPStatusCode::ok);
    response.setBody("Hello World!");
    std::string responseString = response.toString();

    Error error;
    // TODO: should just throw an exception
    BinaryFile file = BinaryFile::Create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    file.write(responseString.c_str(), responseString.length(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("HTTPResponseTests_ToStringTest2.bin");
    ISHIKO_TEST_PASS();
}
