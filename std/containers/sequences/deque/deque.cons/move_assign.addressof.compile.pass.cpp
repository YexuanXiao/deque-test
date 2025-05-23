//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"

// deque& operator=(deque&& c);

// Validate whether the container can be copy-assigned with an ADL-hijacking operator&

#include "deque.hpp"

#include "test_macros.h"
#include "operator_hijacker.h"

void test() {
  bizwen::deque<operator_hijacker> dqo;
  bizwen::deque<operator_hijacker> dq;
  dq = dqo;
}
