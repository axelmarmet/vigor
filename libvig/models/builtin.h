#pragma once

#include <stdint.h>

// Pretend we support those
#ifndef __SSE3__
#  define __SSE3__
#endif

#ifndef __SSSE3__
#  define __SSSE3__
#endif

#ifndef __SSE4_1__
#  define __SSE4_1__
#endif

#ifndef __SSE4_2__
#  define __SSE4_2__
#endif

// Pretend that everything is known to be a compile-time constant, so DPDK uses
// less fancy tricks
#define __builtin_constant_p(x) 1

// Standard CAS (but of course we don't need atomicity)
#define __sync_bool_compare_and_swap(ptr, oldval, newval)                      \
  ((*ptr == oldval) ? (*ptr = newval, 1) : 0)

// DPDK only uses it as an atomic add, no fetch necessary
// TODO make it decent anyway, we shouldn't rely on that
#define __sync_fetch_and_add(ptr, value) (*(ptr) += (value))

// idem than add, but with sub
#define __sync_fetch_and_sub(ptr, value) (*(ptr) -= (value))

// We are single threaded, no need to support thread-local storage
#define __thread

// "This built-in function implements an atomic compare and exchange operation.
//  This compares the contents of *ptr with the contents of *expected.
//  If equal, the operation is a read-modify-write operation that writes desired into *ptr.
//  If they are not equal, the operation is a read and the current contents of *ptr are written into *expected.
//  weak is true for weak compare_exchange, which may fail spuriously, and false for the strong variation, which never fails spuriously.
//  Many targets only offer the strong variation and ignore the parameter. When in doubt, use the strong variation.
//  If desired is written into *ptr then true is returned and memory is affected according to the memory order specified by success_memorder.
//  There are no restrictions on what memory order can be used here.
//  Otherwise, false is returned and memory is affected according to failure_memorder.
//  This memory order cannot be __ATOMIC_RELEASE nor __ATOMIC_ACQ_REL. It also cannot be a stronger order than that specified by success_memorder."
#define __atomic_compare_exchange_n(ptr, expected, desired, weak, success_memorder, failure_memorder) stub_compare_exchange_n(ptr, expected, desired)
// Specialize for volatile int, that's what DPDK uses, and no need for atomicity since we're single-threaded
// and return 'int' because DPDK doesn't like stdbool... ixgbe_osdep literally typedefs bool to int
static inline int stub_compare_exchange_n(volatile int* ptr, volatile int* expected, int desired) {
  if (*ptr == *expected) {
    *ptr = desired;
    return 1;
  } else {
    *expected = *ptr;
    return 0;
  }
}
// Despite it being called test_and_set, GCC docs describe it as "not a
// traditional test-and-set operation, but rather an atomic exchange operation"
static inline int32_t stub_test_and_set(volatile int32_t *ptr, int32_t value) {
  int32_t prev = *ptr;
  *ptr = value;
  return prev;
}
#define __sync_lock_test_and_set stub_test_and_set
