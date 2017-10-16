//
// Created by shiyang on 9/12/17.
//

#include <iostream>
#include <vector>
#include <utility>
#include <sys/time.h>

#include "net.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;


struct Custom {
    int first;
    int second;

    Custom(int f, int s) : first(f), second(s){};
};

void vect_pair(int num) {
    vector<pair<int, int>> vec;
    for (int i = 0; i < num; ++i) {
        vec.emplace_back(i, i + 1);
    }
}


void vect_self_struct(int num) {
    vector<Custom> vec;
    for (int i = 0; i < num; ++i) {
        vec.emplace_back(i, i + 1);
    }
}



void main() {

    struct timeval start,
                    end;
    int num = 10000;

    gettimeofday(&start, nullptr);
    vect_self_struct(num);
    gettimeofday(&end, nullptr);

    long long vect_self_struct_cost = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    cout << "vect_self_struct_cost: " << vect_self_struct_cost << endl;

    gettimeofday(&start, nullptr);
    vect_pair(num);
    gettimeofday(&end, nullptr);

    long long vect_pair_time_cost = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    cout << "vect_pair_time_cost: " << vect_pair_time_cost << endl;


    cout << vect_self_struct_cost  / static_cast<double>(vect_pair_time_cost) << endl;
}