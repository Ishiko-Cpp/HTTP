/*
    Copyright (c) 2022 Xavier Leclercq
    All rights reserved.
*/

#ifndef _ISHIKO_HTTP_TESTS_CLIENTTESTS_H_
#define _ISHIKO_HTTP_TESTS_CLIENTTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class ClientTests : public Ishiko::Tests::TestSequence
{
public:
    ClientTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void GetTest1(Ishiko::Tests::Test& test);
};

#endif
