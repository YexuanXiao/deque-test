//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"

// class deque

// bool empty() const noexcept;

// UNSUPPORTED: c++03, c++11, c++14, c++17

#include "deque.hpp"

void f() {
  bizwen::deque<int> c;
  c.empty(); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
}
