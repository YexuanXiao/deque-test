//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// "deque.hpp"

// iterator insert(const_iterator p, initializer_list<value_type> il);

#include "asan_testing.h"
#include "deque.hpp"
#include <cassert>

#include "test_macros.h"
#include "min_allocator.h"

int main(int, char**) {
  {
    bizwen::deque<int> d(10, 1);
    bizwen::deque<int>::iterator i = d.insert(d.cbegin() + 2, {3, 4, 5, 6});
    assert(d.size() == 14);
    assert(i == d.begin() + 2);
    assert(d[0] == 1);
    assert(d[1] == 1);
    assert(d[2] == 3);
    assert(d[3] == 4);
    assert(d[4] == 5);
    assert(d[5] == 6);
    assert(d[6] == 1);
    assert(d[7] == 1);
    assert(d[8] == 1);
    assert(d[9] == 1);
    assert(d[10] == 1);
    assert(d[11] == 1);
    assert(d[12] == 1);
    assert(d[13] == 1);
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(d));
  }
  {
    bizwen::deque<int, min_allocator<int>> d(10, 1);
    bizwen::deque<int, min_allocator<int>>::iterator i = d.insert(d.cbegin() + 2, {3, 4, 5, 6});
    assert(d.size() == 14);
    assert(i == d.begin() + 2);
    assert(d[0] == 1);
    assert(d[1] == 1);
    assert(d[2] == 3);
    assert(d[3] == 4);
    assert(d[4] == 5);
    assert(d[5] == 6);
    assert(d[6] == 1);
    assert(d[7] == 1);
    assert(d[8] == 1);
    assert(d[9] == 1);
    assert(d[10] == 1);
    assert(d[11] == 1);
    assert(d[12] == 1);
    assert(d[13] == 1);
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(d));
  }

  return 0;
}
