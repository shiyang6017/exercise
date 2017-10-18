//
// Created b_y shiyang on 10/7/17.
//

#ifndef EXERCISE_UTIL_H
#define EXERCISE_UTIL_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define PCHECK(ret) \
do { \
        if (__builtin_expect((ret) != 0, 0)) { \
            fprintf(stderr, "file: %s, line: %d, errno: %s\n", __FILE__, __LINE__, strerror(errno)); \
            exit(errno) ; \
        } \
} while(0)

#define CHECK(ret) \
do { \
        if (__builtin_expect((ret) == 0, 0)) { \
            fprintf(stderr, "file: %s, line: %d, errno: %s\n", __FILE__, __LINE__, strerror(errno)); \
            exit(errno) ; \
        } \
} while(0)

#endif //EXERCISE_UTIL_H
