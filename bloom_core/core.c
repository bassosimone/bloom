#include "core.h"

#include <stdio.h>

/* TODO(bassosimone): when linking statically with GNU libc there is the
   problem of nsswitch, which basically implies we cannot really statically
   link unless we recompile GNU libc. As such, a better test case would
   probably need to call getaddrinfo() here, so to trigger networking. */

int bloom_core_initialize(void) {
  (void)fprintf(stderr, "bloom_core_initialize\n");
  return 0;
}
