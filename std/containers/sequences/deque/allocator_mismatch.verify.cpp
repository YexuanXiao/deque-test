//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// "deque.hpp"
//   The container's value type must be the same as the allocator's value type

#include "deque.hpp"

bizwen::deque<int, std::allocator<long> > d;
// expected-error-re@*:* {{static assertion failed{{.*}}Allocator::value_type must be same type as value_type}}
