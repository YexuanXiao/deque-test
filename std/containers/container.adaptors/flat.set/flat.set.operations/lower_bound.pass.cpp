//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20

// <flat_set>

//       iterator lower_bound(const key_type& k);
// const_iterator lower_bound(const key_type& k) const;

#include <cassert>
#include <deque>
#include <flat_set>
#include <functional>
#include <utility>

#include "MinSequenceContainer.h"
#include "test_macros.h"
#include "min_allocator.h"

template <class KeyContainer>
void test_one() {
  using Key = typename KeyContainer::value_type;
  {
    using M = std::flat_set<Key, std::less<>, KeyContainer>;
    M m     = {1, 2, 4, 5, 8};
    ASSERT_SAME_TYPE(decltype(m.lower_bound(0)), typename M::iterator);
    ASSERT_SAME_TYPE(decltype(std::as_const(m).lower_bound(0)), typename M::const_iterator);
    assert(m.lower_bound(0) == m.begin());
    assert(m.lower_bound(1) == m.begin());
    assert(m.lower_bound(2) == m.begin() + 1);
    assert(m.lower_bound(3) == m.begin() + 2);
    assert(m.lower_bound(4) == m.begin() + 2);
    assert(m.lower_bound(5) == m.begin() + 3);
    assert(m.lower_bound(6) == m.begin() + 4);
    assert(m.lower_bound(7) == m.begin() + 4);
    assert(std::as_const(m).lower_bound(8) == m.begin() + 4);
    assert(std::as_const(m).lower_bound(9) == m.end());
  }
  {
    using M = std::flat_set<Key, std::greater<int>, KeyContainer>;
    M m     = {1, 2, 4, 5, 8};
    ASSERT_SAME_TYPE(decltype(m.lower_bound(0)), typename M::iterator);
    ASSERT_SAME_TYPE(decltype(std::as_const(m).lower_bound(0)), typename M::const_iterator);
    assert(m.lower_bound(0) == m.end());
    assert(m.lower_bound(1) == m.begin() + 4);
    assert(m.lower_bound(2) == m.begin() + 3);
    assert(m.lower_bound(3) == m.begin() + 3);
    assert(m.lower_bound(4) == m.begin() + 2);
    assert(m.lower_bound(5) == m.begin() + 1);
    assert(m.lower_bound(6) == m.begin() + 1);
    assert(m.lower_bound(7) == m.begin() + 1);
    assert(std::as_const(m).lower_bound(8) == m.begin());
    assert(std::as_const(m).lower_bound(9) == m.begin());
  }
  {
    // empty
    using M = std::flat_set<Key, std::less<>, KeyContainer>;
    M m;
    assert(m.lower_bound(0) == m.end());
  }
}

void test() {
  test_one<std::vector<int>>();
  test_one<std::deque<int>>();
  test_one<MinSequenceContainer<int>>();
  test_one<std::vector<int, min_allocator<int>>>();
}

int main(int, char**) {
  test();

  return 0;
}
