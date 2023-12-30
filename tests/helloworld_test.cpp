#include <gtest/gtest.h>

#include "config.h"

TEST(HelloTest, BasicAssertion) {
    EXPECT_LT(PROJECT_VERSION_PATCH, 100);
}
