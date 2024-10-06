// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSETESTS_HPP
#define GUARD_ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSETESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class HTTPResponseTests : public Ishiko::TestSequence
{
public:
    HTTPResponseTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void NotFoundTest1(Ishiko::Test& test);
    static void ToStringTest1(Ishiko::Test& test);
    static void ToStringTest2(Ishiko::Test& test);
};

#endif
