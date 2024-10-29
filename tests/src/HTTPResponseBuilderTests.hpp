// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSEBUILDERTESTS_HPP
#define GUARD_ISHIKO_CPP_HTTP_TESTS_HTTPRESPONSEBUILDERTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class HTTPResponseBuilderTests : public Ishiko::TestSequence
{
public:
    HTTPResponseBuilderTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
