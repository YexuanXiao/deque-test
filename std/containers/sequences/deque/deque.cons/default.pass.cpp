//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"

// deque()

#include "asan_testing.h"
#include "deque.hpp"
#include <cassert>

#include "test_macros.h"
#include "test_allocator.h"
#include "../../../NotConstructible.h"
#include "min_allocator.h"

template <class T, class Allocator>
void test() {
  bizwen::deque<T, Allocator> d;
  assert(d.size() == 0);
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(d));
#if TEST_STD_VER >= 11
  bizwen::deque<T, Allocator> d1 = {};
  assert(d1.size() == 0);
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(d1));
#endif
}

int main(int, char**) {
  test<int, std::allocator<int> >();
  test<NotConstructible, limited_allocator<NotConstructible, 1> >();
#if TEST_STD_VER >= 11
  test<int, min_allocator<int> >();
  test<NotConstructible, min_allocator<NotConstructible> >();
#endif

  return 0;
}
