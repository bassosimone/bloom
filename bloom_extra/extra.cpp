#include "extra.h"

#include <future>
#include <iostream>
#include <mutex>

// The main reason why we're using threading stuff here is because the
// default build of mingw-w64 doesn't support C++11 threading.
//
// See: https://github.com/Homebrew/homebrew-core/issues/21706

int bloom_extra_initialize() noexcept {
  std::mutex mutex;
  std::async(std::launch::async, [&]() {
    std::unique_lock<std::mutex> _{mutex};
    std::clog << "bloom_extra_initialize" << std::endl;
  });
  return 0;
}
