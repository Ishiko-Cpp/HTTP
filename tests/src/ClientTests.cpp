/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#include "ClientTests.hpp"

using namespace Ishiko::Tests;

ClientTests::ClientTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Client tests", context)
{
    append<HeapAllocationErrorsTest>("Get test 1", GetTest1);
}

void ClientTests::GetTest1(Test& test)
{
}
