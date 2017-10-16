//
// Created by shiyang on 10/14/17.
//



#include <gtest/gtest.h>

#include "environment.h"

using namespace unitTest;

std::unique_ptr<SharedResource> FooTest::sharedResource;

namespace {

    // test object
    TEST_F(FooTest, TEST_FIRST) {
        privateResource->setVal(1);
        sharedResource->setVal(1);
    }

    TEST_F(FooTest, TEST_SECOND) {
        std::cout << privateResource->getVal() << std::endl;
        std::cout << sharedResource->getVal() << std::endl;
    }
}

    int main(int argc, char *argv[]) {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
