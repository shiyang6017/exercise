//
// Created by shiyang on 10/15/17.
//
#include <gtest/gtest.h>
#include "environment.h"
using namespace unitTest;

namespace {
    //value parameteruzed tests

    // step 1
    class IntegerTest : public ::testing::TestWithParam<Integer> {
    public:
        ~IntegerTest() override = default;

        void SetUp() override {
            integer = GetParam();
        }
        void TearDown() override {
            // todo;
        }

    protected:
        Integer integer;
    };

    // step 2
    TEST_P(IntegerTest, PrefixIncrement) {
        int expectVal = integer.getVal() + 1;
        EXPECT_EQ(expectVal, (++integer).getVal());
    }

    TEST_P(IntegerTest, SufixIncrement) {
        int expectVal = integer.getVal();
        EXPECT_EQ(expectVal, (integer++).getVal());

        ++expectVal;
        EXPECT_EQ(expectVal, integer.getVal());

    }

    // step 3
    INSTANTIATE_TEST_CASE_P(IntegerTest_Part1, IntegerTest, ::testing::Values(Integer(0), Integer(1)));
    INSTANTIATE_TEST_CASE_P(IntegerTest_Part2, IntegerTest, ::testing::Values(Integer(2), Integer(3)));
}



int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}