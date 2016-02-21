#include <klee/klee.h>
#include "lib/expirator.h"
#include "containers/double-chain-stub-control.h"


int expire_items(struct DoubleChain* chain, struct DoubleMap* map,
                 uint32_t time) {
  klee_trace_param_i32(time, "exp_time");
  int nfreed = klee_int("number_of_freed_flows");
  klee_assume(0 <= nfreed);
  if (nfreed > 0)
    dchain_allocate_some(chain);
  //Tell dchain model that we freed some indexes here
  return nfreed;
}
