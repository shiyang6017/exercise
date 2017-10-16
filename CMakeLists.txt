cmake_minimum_required(VERSION 3.8)
project(exercise)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        boost/implicit_cast.cc
        c++11/final&override.cc
        c++11/function&bind.cc
        c++11/test.cc
        data_structure/ex_string.cc
        data_structure/ex_string.h
        data_structure/ex_string_test.cc
        data_structure/ex_swap.h
        data_structure/ex_swap_test.cc
        design_pattern/strategy.cc
        design_pattern/strategy.h
        concurrency/rwlock.cc
        template/partial-specialization.cc
        template/specializion_of_a_class_member.cc network/eof.c network/server.c network/client.c network/sleep1.c network/sync_using_signal.c concurrency/rwlock.c network/test.c network/mmap.c network/anon_mmap.c network/signalfd.c network/epoll.c concurrency/producer_comsumer.cpp concurrency/test.c concurrency/concu.c c++11/SFINAE.cc network/net.h network/net.c concurrency/question_1.cc concurrency/question_2.cc concurrency/definition.cc c++11/vector_pair.cc "operating system/signalfd_test.c" "operating system/eventfd_test.c" "operating system/timerfd_test.c" ipc/posix_shm.cc ipc/Util.h debug-tools/valgrind/Memcheck_test.cc debug-tools/valgrind/Helgrind_test.cc test.cc debug-tools/valgrind/callgrind_test_part1.cc debug-tools/valgrind/callgrind_test_part2.cc debug-tools/gtest/assert.cc template/static_assert.cc debug-tools/gtest/TEST.cc debug-tools/gtest/TEST_F.cc debug-tools/gtest/environment.h debug-tools/gtest/TEST_P.cc debug-tools/gtest/TYPED_TEST_P.cc)

add_executable(exercise ${SOURCE_FILES})