#ifndef _BOILERPLATE_UTIL_H_INCLUDED_
#define _BOILERPLATE_UTIL_H_INCLUDED_

#include <stdint.h>
#include <limits.h>

#include "include_ignored_by_verifast.h"

#ifdef _NO_VERIFAST_
#  define IGNORE(x) (void)(x)
#else //_NO_VERIFAST_
#  define IGNORE(x)
#endif //_NO_VERIFAST_

//TODO: replace this with a cheaper(performancewise) equivalent:
/*@
  fixpoint long long _wrap(long long x) { return x % INT_MAX; }
  @*/

// KLEE doesn't tolerate && in a klee_assume (see klee/klee#809),
// so we replace them with & during symbex but interpret them as && in the validator
#ifdef KLEE_VERIFICATION
#  define AND &
#else // KLEE_VERIFICATION
#  define AND &&
#endif // KLEE_VERIFICATION

static inline unsigned long long wrap(unsigned long long x)
//@ requires true;
//@ ensures result == _wrap(x) &*& INT_MIN <= result &*& result <= INT_MAX;
{
  //@ div_rem(x, INT_MAX);
  return x % INT_MAX;
}

static void null_init(void* obj)
/*@ requires chars(obj, sizeof(uint32_t), _); @*/
/*@ ensures u_integer(obj, _); @*/
{
  *(uint32_t*)obj = 0;
}

#ifdef KLEE_VERIFICATION
#include <klee/klee.h>
static inline void
concretize_devices(uint16_t device, uint16_t count) {
	klee_assert(device >= 0);
	klee_assert(device < count);

	for(unsigned d = 0; d < count; d++) if (device == d) { device = d; break; }
}
#endif//KLEE_VERIFICATION



#endif//_BOILERPLATE_UTIL_H_INCLUDED_