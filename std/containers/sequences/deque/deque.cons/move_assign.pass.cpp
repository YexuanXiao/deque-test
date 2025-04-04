//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// "deque.hpp"

// deque& operator=(deque&& c);

#include "asan_testing.h"
#include "deque.hpp"
#include <cassert>

#include "test_macros.h"
#include "MoveOnly.h"
#include "test_allocator.h"
#include "min_allocator.h"

int main(int, char**) {
  {
    int ab[] = {3, 4, 2, 8, 0, 1, 44, 34, 45, 96, 80, 1, 13, 31, 45};
    int* an  = ab + sizeof(ab) / sizeof(ab[0]);
    typedef test_allocator<MoveOnly> A;
    bizwen::deque<MoveOnly, A> c1(A(5));
    for (int* p = ab; p < an; ++p)
      c1.push_back(MoveOnly(*p));
    bizwen::deque<MoveOnly, A> c2(A(5));
    for (int* p = ab; p < an; ++p)
      c2.push_back(MoveOnly(*p));
    bizwen::deque<MoveOnly, A> c3(A(5));
    c3 = std::move(c1);
    assert(c2 == c3);
    assert(c1.size() == 0);
    assert(c3.get_allocator() == A(5));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c1));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c2));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c3));
  }
  {
    int ab[] = {3, 4, 2, 8, 0, 1, 44, 34, 45, 96, 80, 1, 13, 31, 45};
    int* an  = ab + sizeof(ab) / sizeof(ab[0]);
    typedef test_allocator<MoveOnly> A;
    bizwen::deque<MoveOnly, A> c1(A(5));
    for (int* p = ab; p < an; ++p)
      c1.push_back(MoveOnly(*p));
    bizwen::deque<MoveOnly, A> c2(A(5));
    for (int* p = ab; p < an; ++p)
      c2.push_back(MoveOnly(*p));
    bizwen::deque<MoveOnly, A> c3(A(6));
    c3 = std::move(c1);
    assert(c2 == c3);
    assert(c1.size() != 0);
    assert(c3.get_allocator() == A(6));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c1));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c2));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c3));
  }
  {
    int ab[] = {3, 4, 2, 8, 0, 1, 44, 34, 45, 96, 80, 1, 13, 31, 45};
    int* an  = ab + sizeof(ab) / sizeof(ab[0]);
    typedef other_allocator<MoveOnly> A;
    bizwen::deque<MoveOnly, A> c1(A(5));
    for (int* p = ab; p < an; ++p)
      c1.push_back(MoveOnly(*p));
    bizwen::deque<MoveOnly, A> c2(A(5));
    for (int* p = ab; p < an; ++p)
      c2.push_back(MoveOnly(*p));
    bizwen::deque<MoveOnly, A> c3(A(6));
    c3 = std::move(c1);
    assert(c2 == c3);
    assert(c1.size() == 0);
    assert(c3.get_allocator() == A(5));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c1));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c2));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c3));
  }
  {
    int ab[] = {3, 4, 2, 8, 0, 1, 44, 34, 45, 96, 80, 1, 13, 31, 45};
    int* an  = ab + sizeof(ab) / sizeof(ab[0]);
    typedef min_allocator<MoveOnly> A;
    bizwen::deque<MoveOnly, A> c1(A{});
    for (int* p = ab; p < an; ++p)
      c1.push_back(MoveOnly(*p));
    bizwen::deque<MoveOnly, A> c2(A{});
    for (int* p = ab; p < an; ++p)
      c2.push_back(MoveOnly(*p));
    bizwen::deque<MoveOnly, A> c3(A{});
    c3 = std::move(c1);
    assert(c2 == c3);
    assert(c1.size() == 0);
    assert(c3.get_allocator() == A());
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c1));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c2));
    LIBCPP_ASSERT(is_double_ended_contiguous_container_asan_correct(c3));
  }

  return 0;
}
