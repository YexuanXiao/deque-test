//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// UNSUPPORTED: c++03, c++11, c++14, c++17

// <vector>

// template <class T, class Allocator, class Predicate>
//   typename vector<T, Allocator>::size_type
//   erase_if(vector<T, Allocator>& c, Predicate pred);

#include <vector>

#include "test_macros.h"
#include "test_allocator.h"
#include "min_allocator.h"

template <class S, class Pred>
TEST_CONSTEXPR_CXX20 void test0(S s, Pred p, S expected, std::size_t expected_erased_count) {
  ASSERT_SAME_TYPE(typename S::size_type, decltype(std::erase_if(s, p)));
  assert(expected_erased_count == std::erase_if(s, p));
  assert(s == expected);
}

template <typename S>
TEST_CONSTEXPR_CXX20 void test() {
  auto is1   = [](auto v) { return v == 1; };
  auto is2   = [](auto v) { return v == 2; };
  auto is3   = [](auto v) { return v == 3; };
  auto is4   = [](auto v) { return v == 4; };
  auto True  = [](auto) { return true; };
  auto False = [](auto) { return false; };

  test0(S(), is1, S(), 0);

  test0(S({1}), is1, S(), 1);
  test0(S({1}), is2, S({1}), 0);

  test0(S({1, 2}), is1, S({2}), 1);
  test0(S({1, 2}), is2, S({1}), 1);
  test0(S({1, 2}), is3, S({1, 2}), 0);
  test0(S({1, 1}), is1, S(), 2);
  test0(S({1, 1}), is3, S({1, 1}), 0);

  test0(S({1, 2, 3}), is1, S({2, 3}), 1);
  test0(S({1, 2, 3}), is2, S({1, 3}), 1);
  test0(S({1, 2, 3}), is3, S({1, 2}), 1);
  test0(S({1, 2, 3}), is4, S({1, 2, 3}), 0);

  test0(S({1, 1, 1}), is1, S(), 3);
  test0(S({1, 1, 1}), is2, S({1, 1, 1}), 0);
  test0(S({1, 1, 2}), is1, S({2}), 2);
  test0(S({1, 1, 2}), is2, S({1, 1}), 1);
  test0(S({1, 1, 2}), is3, S({1, 1, 2}), 0);
  test0(S({1, 2, 2}), is1, S({2, 2}), 1);
  test0(S({1, 2, 2}), is2, S({1}), 2);
  test0(S({1, 2, 2}), is3, S({1, 2, 2}), 0);

  test0(S({1, 2, 3}), True, S(), 3);
  test0(S({1, 2, 3}), False, S({1, 2, 3}), 0);
}

TEST_CONSTEXPR_CXX20 bool tests() {
  test<std::vector<int>>();
  test<std::vector<int, min_allocator<int>>>();
  test<std::vector<int, test_allocator<int>>>();
  test<std::vector<int, safe_allocator<int>>>();

  test<std::vector<long>>();
  test<std::vector<double>>();

  return true;
}

int main(int, char**) {
  tests();
#if TEST_STD_VER > 17
  static_assert(tests());
#endif
  return 0;
}
