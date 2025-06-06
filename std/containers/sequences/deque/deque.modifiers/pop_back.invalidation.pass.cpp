//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"

// void pop_back()

//  Erasing items from the beginning or the end of a deque shall not invalidate iterators
//  to items that were not erased.

#include "asan_testing.h"
#include "deque.hpp"
#include <cassert>

#include "test_macros.h"

template <typename C>
void test(C c) {
  typename C::iterator it1 = c.begin();
  typename C::iterator it2 = c.end() - 2;

  c.pop_back();

  typename C::iterator it3 = c.begin();
  typename C::iterator it4 = c.end() - 1;
  assert(it1 == it3);
  assert(*it1 == *it3);
  assert(&*it1 == &*it3);
  assert(it2 == it4);
  assert(*it2 == *it4);
  assert(&*it2 == &*it4);
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c));
}

int main(int, char**) {
  bizwen::deque<int> queue;
  for (int i = 0; i < 4098; ++i)
    queue.push_back(i);

  while (queue.size() > 1) {
    test(queue);
    queue.pop_back();
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(queue));
  }

  return 0;
}
