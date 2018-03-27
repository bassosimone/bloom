#include "core.h"

#define _WIN32_WINNT 0x0600 /* Expose AI_NUMERICSERV */

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#endif

#include <stdio.h>
#include <string.h>

/* When linking statically with GNU libc there is the problem of
   nsswitch, which basically implies we cannot really statically link
   unless we recompile GNU libc. This is the reason why we are using
   getaddrinfo() here, because it looks like a good test case that
   would break if we attempt to pass `-static` to gcc on Linux.

   See: https://stackoverflow.com/questions/3430400. */

int bloom_core_initialize(void) {
  struct addrinfo *rp = NULL;
  struct addrinfo hints;
  memset(&hints, 0, sizeof (hints));
  hints.ai_flags |= AI_NUMERICSERV;
  int rv = getaddrinfo("www.kernel.org", "443", &hints, &rp);
  if (rv == 0) freeaddrinfo(rp);
  (void)fprintf(stderr, "bloom_core_initialize: %d\n", rv);
  return 0;
}
