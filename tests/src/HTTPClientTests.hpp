// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_HTTP_TESTS_HTTPCLIENTTESTS_HPP
#define GUARD_ISHIKO_CPP_HTTP_TESTS_HTTPCLIENTTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class HTTPClientTests : public Ishiko::TestSequence
{
public:
    HTTPClientTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void GetTest1(Ishiko::Test& test);
    static void GetTest2(Ishiko::Test& test);
    static void GetTest3(Ishiko::Test& test);
    static void GetTest4(Ishiko::Test& test);
    static void GetTest5(Ishiko::Test& test);
};

#endif
