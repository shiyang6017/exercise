//
// Created by shiyang on 10/15/17.
//
#include <gtest/gtest.h>
#include "environment.h"
using namespace unitTest;

namespace {
    // test template
    template<typename T>
    class TemplateTest : public  ::testing::Test {
    public:
        ~TemplateTest() override = default;

        void SetUp() override {
            value = 0;
        }

        void TearDown() override { }

    protected:
        T value;
    };

    TYPED_TEST_CASE_P(TemplateTest);

    TYPED_TEST_P(TemplateTest, TemplateTestEQ) {
        TypeParam zero(0);

        //todo: when just use value, this is a compile error. why ?
        // Answer : this is not a TemplateTest class, operator -> is being overrode ?
        EXPECT_EQ(zero, this->value);
    }

    TYPED_TEST_P(TemplateTest, TemplateTestLT) {

        TypeParam zero(0);

        EXPECT_LT(zero, this->value);
    }

    REGISTER_TYPED_TEST_CASE_P(TemplateTest, TemplateTestEQ, TemplateTestLT);

    typedef testing::Types<int, Integer> TestedType;

    INSTANTIATE_TYPED_TEST_CASE_P(Number, TemplateTest, TestedType);

}


int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}