//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"

// void resize(size_type n, const value_type& v);

#include "asan_testing.h"
#include "deque.hpp"
#include <algorithm>
#include <iterator>
#include <cassert>
#include <cstddef>

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
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c));
  for (int i = 0; i < size; ++i)
    c.push_back(i);
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c));
  for (int i = 0; i < start; ++i)
    c.pop_front();
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c));
  return c;
}

template <class C>
void test(C& c1, int size, int x) {
  typedef typename C::const_iterator CI;
  typename C::size_type c1_osize = c1.size();
  c1.resize(size, x);
  assert(c1.size() == static_cast<std::size_t>(size));
  assert(static_cast<std::size_t>(std::distance(c1.begin(), c1.end())) == c1.size());
  LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c1));
  CI i = c1.begin();
  for (int j = 0; static_cast<std::size_t>(j) < std::min(c1_osize, c1.size()); ++j, ++i)
    assert(*i == j);
  for (std::size_t j = c1_osize; j < c1.size(); ++j, ++i)
    assert(*i == x);
}

template <class C>
void testN(int start, int N, int M) {
  C c1 = make<C>(N, start);
  test(c1, M, -10);
}

int main(int, char**) {
  {
    int rng[]   = {0, 1, 2, 3, 1023, 1024, 1025, 2047, 2048, 2049};
    const int N = sizeof(rng) / sizeof(rng[0]);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        for (int k = 0; k < N; ++k)
          testN<bizwen::deque<int> >(rng[i], rng[j], rng[k]);
  }
#if TEST_STD_VER >= 11
  {
    int rng[]   = {0, 1, 2, 3, 1023, 1024, 1025, 2047, 2048, 2049};
    const int N = sizeof(rng) / sizeof(rng[0]);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        for (int k = 0; k < N; ++k)
          testN<bizwen::deque<int, min_allocator<int>>>(rng[i], rng[j], rng[k]);
  }
  {
    int rng[]   = {0, 1, 2, 3, 1023, 1024, 1025, 2047, 2048, 2049};
    const int N = sizeof(rng) / sizeof(rng[0]);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        for (int k = 0; k < N; ++k)
          testN<bizwen::deque<int, safe_allocator<int>>>(rng[i], rng[j], rng[k]);
  }
#endif

  return 0;
}
