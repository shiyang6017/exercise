#ifndef _EXERCISE_SWAP_H
#define _EXERCISE_SWAP_H

#include "ex_string.h"

/*
 * only partially specialization is allow in namespace std, 
 * add new func or overload func is forbidded
 */
namespace std {
template<>
void swap<exercise::String>(exercise::String& lhs, 
                                 exercise::String& rhs)
{
    lhs.swap(rhs);
}

}

#endif