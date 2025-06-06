//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"

// void push_back(const value_type& v);
// void pop_back();
// void pop_front();

#include "asan_testing.h"
#include "deque.hpp"
#include <cassert>

#include "test_macros.h"
#include "min_allocator.h"

template <class C>
C make(int size, int start = 0) {
  const int b = 4096 / sizeof(int);
  int init    = 0;
  if (start > 0) {
    init = (start + 1) / b + ((start + 1) % b != 0);
    init *= b;
    --init;
  }
  C c(init, 0);
  for (int i = 0; i < init - start; ++i)
    c.pop_back();
  for (int i = 0; i < size; ++i)
    c.push_back(i);
  for (int i = 0; i < start; ++i)
    c.pop_front();
  return c;
}

template <class C>
void test(int size) {
  int rng[]   = {0, 1, 2, 3, 1023, 1024, 1025, 2046, 2047, 2048, 2049};
  const int N = sizeof(rng) / sizeof(rng[0]);
  for (int j = 0; j < N; ++j) {
    C c                           = make<C>(size, rng[j]);
    typename C::const_iterator it = c.begin();
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c));
    for (int i = 0; i < size; ++i, ++it)
      assert(*it == i);
  }
}

int main(int, char**) {
  {
    int rng[]   = {0, 1, 2, 3, 1023, 1024, 1025, 2046, 2047, 2048, 2049, 4094, 4095, 4096};
    const int N = sizeof(rng) / sizeof(rng[0]);
    for (int j = 0; j < N; ++j)
      test<bizwen::deque<int> >(rng[j]);
  }
#if TEST_STD_VER >= 11
  {
    int rng[]   = {0, 1, 2, 3, 1023, 1024, 1025, 2046, 2047, 2048, 2049, 4094, 4095, 4096};
    const int N = sizeof(rng) / sizeof(rng[0]);
    for (int j = 0; j < N; ++j)
      test<bizwen::deque<int, min_allocator<int>> >(rng[j]);
  }
#endif

  return 0;
}
