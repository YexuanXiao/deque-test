//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: no-exceptions
// "deque.hpp"

// void push_back(const value_type& x);

#include "deque.hpp"
#include "test_macros.h"
#include "test_allocator.h"
#include <cassert>

// Flag that makes the copy constructor for CMyClass throw an exception
static bool gCopyConstructorShouldThrow = false;

class CMyClass {
public:
  CMyClass(int tag);

public:
  CMyClass(const CMyClass& iOther);

public:
  ~CMyClass();

  bool equal(const CMyClass& rhs) const { return fTag == rhs.fTag && fMagicValue == rhs.fMagicValue; }

private:
  int fMagicValue;
  int fTag;

private:
  static int kStartedConstructionMagicValue;

private:
  static int kFinishedConstructionMagicValue;
};

// Value for fMagicValue when the constructor has started running, but not yet finished
int CMyClass::kStartedConstructionMagicValue = 0;
// Value for fMagicValue when the constructor has finished running
int CMyClass::kFinishedConstructionMagicValue = 12345;

CMyClass::CMyClass(int tag) : fMagicValue(kStartedConstructionMagicValue), fTag(tag) {
  // Signal that the constructor has finished running
  fMagicValue = kFinishedConstructionMagicValue;
}

CMyClass::CMyClass(const CMyClass& iOther) : fMagicValue(kStartedConstructionMagicValue), fTag(iOther.fTag) {
  // If requested, throw an exception _before_ setting fMagicValue to kFinishedConstructionMagicValue
  if (gCopyConstructorShouldThrow) {
    throw std::exception();
  }
  // Signal that the constructor has finished running
  fMagicValue = kFinishedConstructionMagicValue;
}

CMyClass::~CMyClass() {
  // Only instances for which the constructor has finished running should be destructed
  assert(fMagicValue == kFinishedConstructionMagicValue);
}

bool operator==(const CMyClass& lhs, const CMyClass& rhs) { return lhs.equal(rhs); }

int main(int, char**) {
  CMyClass instance(42);
  {
    bizwen::deque<CMyClass> vec;

    vec.push_back(instance);
    bizwen::deque<CMyClass> vec2(vec);

    gCopyConstructorShouldThrow = true;
    try {
      vec.push_back(instance);
      assert(false);
    } catch (...) {
      gCopyConstructorShouldThrow = false;
      assert(vec == vec2);
    }
  }

  {
    test_allocator_statistics alloc_stats;
    typedef bizwen::deque<CMyClass, test_allocator<CMyClass> > C;
    C vec((test_allocator<CMyClass>(&alloc_stats)));
    C vec2(vec, test_allocator<CMyClass>(&alloc_stats));

    alloc_stats.throw_after = 1;
    try {
      vec.push_back(instance);
      assert(false);
    } catch (...) {
      assert(vec == vec2);
    }
  }

  return 0;
}
