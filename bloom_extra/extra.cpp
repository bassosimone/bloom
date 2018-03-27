#include "extra.h"

#include <iostream>

// TODO(bassosimone): the main thing that blows when using mingw-w64 is
// threading, hence this library should use <thread>.

int bloom_extra_initialize() noexcept {
  std::clog << "bloom_extra_initialize" << std::endl;
  return 0;
}
