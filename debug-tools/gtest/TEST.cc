//
// Created b_y shiyang on 10/14/17.
//

#include <gtest/gtest.h>
namespace {
    // test function
    bool isOdd(int val) {
        return (val & 1) == 1;
    }

    TEST(isOdd, test_isOdd) {
        EXPECT_EQ(true, isOdd(1));
        EXPECT_EQ(false, isOdd(0));
    }

}
    int main(int argc, char *argv[]) {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
