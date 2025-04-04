//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// "deque.hpp"

// void push_front(value_type&& v);

#include "asan_testing.h"
#include "deque.hpp"
#include <cassert>
#include <cstddef>

#include "test_macros.h"
#include "MoveOnly.h"
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
  C c(init);
  for (int i = 0; i < init - start; ++i)
    c.pop_back();
  for (int i = 0; i < size; ++i)
    c.push_back(MoveOnly(i));
  for (int i = 0; i < start; ++i)
    c.pop_front();
  return c;
}

template <class C>
void test(C& c1, int x) {
  typedef typename C::iterator I;
  std::size_t c1_osize = c1.size();
  c1.push_front(MoveOnly(x));
  assert(c1.size() == c1_osize + 1);
  assert(static_cast<std::size_t>(std::distance(c1.begin(), c1.end())) == c1.size());
  I i = c1.begin();
  assert(*i == MoveOnly(x));
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c1));
  ++i;
  for (int j = 0; static_cast<std::size_t>(j) < c1_osize; ++j, (void)++i)
    assert(*i == MoveOnly(j));
}

template <class C>
void testN(int start, int N) {
  C c1 = make<C>(N, start);
  test(c1, -10);
}

int main(int, char**) {
  {
    int rng[]   = {0, 1, 2, 3, 1023, 1024, 1025, 2047, 2048, 2049};
    const int N = sizeof(rng) / sizeof(rng[0]);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        testN<bizwen::deque<MoveOnly> >(rng[i], rng[j]);
  }
  {
    int rng[]   = {0, 1, 2, 3, 1023, 1024, 1025, 2047, 2048, 2049};
    const int N = sizeof(rng) / sizeof(rng[0]);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        testN<bizwen::deque<MoveOnly, safe_allocator<MoveOnly>> >(rng[i], rng[j]);
  }

  return 0;
}
