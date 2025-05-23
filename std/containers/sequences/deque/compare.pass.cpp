//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"

// template<class T, class Alloc>
// bool operator==(const bizwen::deque<T, Alloc>& lhs,
//                 const bizwen::deque<T,Alloc>& rhs);

// template<class T, class Alloc>
// bool operator!=(const bizwen::deque<T,Alloc>& lhs,
//                 const bizwen::deque<T,Alloc>& rhs);

// template<class T, class Alloc>
// bool operator<(const bizwen::deque<T,Alloc>& lhs,
//                const bizwen::deque<T,Alloc>& rhs);

// template<class T, class Alloc>
// bool operator<=(const bizwen::deque<T,Alloc>& lhs,
//                 const bizwen::deque<T,Alloc>& rhs);

// template<class T, class Alloc>
// bool operator>(const bizwen::deque<T,Alloc>& lhs,
//                const bizwen::deque<T,Alloc>& rhs);

// template<class T, class Alloc>
// bool operator>=(const bizwen::deque<T,Alloc>& lhs,
//                 const bizwen::deque<T,Alloc>& rhs);

#include "deque.hpp"
#include <cassert>

#include "test_comparisons.h"

int main(int, char**) {
  {
    const bizwen::deque<int> d1, d2;
    assert(testComparisons(d1, d2, true, false));
  }
  {
    const bizwen::deque<int> d1(1, 1), d2(1, 1);
    assert(testComparisons(d1, d2, true, false));
  }
  {
    int items[3] = {1, 2, 3};
    const bizwen::deque<int> d1(items, items + 3);
    const bizwen::deque<int> d2(items, items + 3);
    assert(testComparisons(d1, d2, true, false));
  }
  {
    const bizwen::deque<int> d1(1, 1), d2;
    assert(testComparisons(d1, d2, false, false));
  }
  {
    const bizwen::deque<int> d1(1, 1), d2(1, 2);
    assert(testComparisons(d1, d2, false, true));
  }
  {
    int items1[2] = {1, 2};
    int items2[2] = {1, 3};
    const bizwen::deque<int> d1(items1, items1 + 2);
    const bizwen::deque<int> d2(items2, items2 + 2);
    assert(testComparisons(d1, d2, false, true));
  }
  {
    int items1[2] = {2, 2};
    int items2[2] = {1, 3};
    const bizwen::deque<int> d1(items1, items1 + 2);
    const bizwen::deque<int> d2(items2, items2 + 2);
    assert(testComparisons(d1, d2, false, false));
  }
  {
    const bizwen::deque<LessAndEqComp> d1, d2;
    assert(testComparisons(d1, d2, true, false));
  }
  {
    const bizwen::deque<LessAndEqComp> d1(1, LessAndEqComp(1));
    const bizwen::deque<LessAndEqComp> d2(1, LessAndEqComp(1));
    assert(testComparisons(d1, d2, true, false));
  }
  {
    LessAndEqComp items[3] = {LessAndEqComp(1), LessAndEqComp(2), LessAndEqComp(3)};
    const bizwen::deque<LessAndEqComp> d1(items, items + 3);
    const bizwen::deque<LessAndEqComp> d2(items, items + 3);
    assert(testComparisons(d1, d2, true, false));
  }
  {
    const bizwen::deque<LessAndEqComp> d1(1, LessAndEqComp(1));
    const bizwen::deque<LessAndEqComp> d2;
    assert(testComparisons(d1, d2, false, false));
  }
  {
    const bizwen::deque<LessAndEqComp> d1(1, LessAndEqComp(1));
    const bizwen::deque<LessAndEqComp> d2(1, LessAndEqComp(2));
    assert(testComparisons(d1, d2, false, true));
  }
  {
    LessAndEqComp items1[2] = {LessAndEqComp(1), LessAndEqComp(2)};
    LessAndEqComp items2[2] = {LessAndEqComp(1), LessAndEqComp(3)};
    const bizwen::deque<LessAndEqComp> d1(items1, items1 + 2);
    const bizwen::deque<LessAndEqComp> d2(items2, items2 + 2);
    assert(testComparisons(d1, d2, false, true));
  }
  {
    LessAndEqComp items1[2] = {LessAndEqComp(2), LessAndEqComp(2)};
    LessAndEqComp items2[2] = {LessAndEqComp(1), LessAndEqComp(3)};
    const bizwen::deque<LessAndEqComp> d1(items1, items1 + 2);
    const bizwen::deque<LessAndEqComp> d2(items2, items2 + 2);
    assert(testComparisons(d1, d2, false, false));
  }

  return 0;
}
