#ifndef BLOOM_CORE_H
#define BLOOM_CORE_H

#ifdef __cplusplus
extern "C" {
#define BLOOM_CORE_NOEXCEPT noexcept
#else
#define BLOOM_CORE_NOEXCEPT /* Nothing */
#endif

int bloom_core_initialize(void) BLOOM_CORE_NOEXCEPT;

#ifdef __cplusplus
}
#endif
#endif
