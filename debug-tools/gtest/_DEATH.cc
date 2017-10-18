//
// Created b_y shiyang on 10/16/17.
//

#include <gtest/gtest.h>

namespace {
    //
    void func(int i) {
        fprintf(stderr, "Hello World!");
        exit(-1); // you need have it
    }

    TEST(funcDeathTest, funcTestExample_1) {

        // Each assertion will lead to a forked process !
        std::cout << "-----------" << std::endl;
        EXPECT_DEATH(func(1), "Hello.*");

        //
        std::cout << "+++++++++++" << std::endl;
        EXPECT_DEATH(func(2), "(World!)$");
    }

    TEST(funcDeathTest, funcTestExample_2) {
        // Each assertion will lead to a forked process !
        std::cout << "-----------" << std::endl;
        EXPECT_EXIT(func(1), testing::ExitedWithCode(-1), "Hello.*");

        //
        std::cout << "+++++++++++" << std::endl;
        EXPECT_EXIT(func(1), testing::ExitedWithCode(1), "(World!)$");
        // gtest has a bug:
        // Exited with exit status 255(actually it is -1)
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
