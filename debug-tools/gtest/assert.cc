//
// Created by shiyang on 10/14/17.
//
#include <gtest/gtest.h>
using namespace std;

int func_sum(int a, int b) { return a + b; }

bool func_bool(int i) { return (i&1) != 0; }

void unit_test_a() {

    EXPECT_EQ(4, func_sum(1, 2)) << "EXPECT_EQ()";

    //ASSERT_* 系列的断言，当检查点失败时，退出当前函数（注意：并非退出当前test case）
    ASSERT_EQ(4, func_sum(1,2)) << "EXPECT_EQ()";

    //不会执行到这里
    std::cout << "Every Thing is done!" << std::endl;
}


void unit_test_b() {

    EXPECT_EQ(true, func_bool(1));

    // 直接退出
    FAIL() << "FAIL()";

    EXPECT_EQ(true, func_bool(1));
}

void unit_test_c() {

    EXPECT_TRUE(func_bool(0));
    ASSERT_FALSE(func_bool(1));
}



void unit_test_d() {
    int first = 1, second = 2;
    ASSERT_EQ(true, func_bool(first)) << "first = " << first;
}


void seperate() {

    std::cout << "------------------" << std::endl << std::endl;

}

int main() {

    unit_test_a();
    seperate();

    unit_test_b();
    seperate();

    unit_test_c();
    seperate();

    unit_test_d();
    seperate();

    return 0;
}