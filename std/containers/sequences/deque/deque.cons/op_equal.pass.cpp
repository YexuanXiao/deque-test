//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"

// deque& operator=(const deque& c);

#include "asan_testing.h"
#include "deque.hpp"
#include <cassert>
#include "test_macros.h"
#include "test_allocator.h"
#include "min_allocator.h"

template <class C>
void test(const C& x) {
  C c;
  c = x;
  assert(c == x);
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c));
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(x));
}

int main(int, char**) {
  {
    int ab[] = {3, 4, 2, 8, 0, 1, 44, 34, 45, 96, 80, 1, 13, 31, 45};
    int* an  = ab + sizeof(ab) / sizeof(ab[0]);
    test(bizwen::deque<int>(ab, an));
  }
  {
    bizwen::deque<int, test_allocator<int> > l(3, 2, test_allocator<int>(5));
    bizwen::deque<int, test_allocator<int> > l2(l, test_allocator<int>(3));
    l2 = l;
    assert(l2 == l);
    assert(l2.get_allocator() == test_allocator<int>(3));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(l));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(l2));
  }
  {
    bizwen::deque<int, other_allocator<int> > l(3, 2, other_allocator<int>(5));
    bizwen::deque<int, other_allocator<int> > l2(l, other_allocator<int>(3));
    l2 = l;
    assert(l2 == l);
    assert(l2.get_allocator() == other_allocator<int>(5));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(l));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(l2));
  }
#if TEST_STD_VER >= 11
  {
    int ab[] = {3, 4, 2, 8, 0, 1, 44, 34, 45, 96, 80, 1, 13, 31, 45};
    int* an  = ab + sizeof(ab) / sizeof(ab[0]);
    test(bizwen::deque<int, min_allocator<int>>(ab, an));
  }
  {
    bizwen::deque<int, min_allocator<int> > l(3, 2, min_allocator<int>());
    bizwen::deque<int, min_allocator<int> > l2(l, min_allocator<int>());
    l2 = l;
    assert(l2 == l);
    assert(l2.get_allocator() == min_allocator<int>());
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(l));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(l2));
  }
#endif

  return 0;
}
