#ifndef BLOOM_EXTRA_H
#define BLOOM_EXTRA_H

#ifdef __cplusplus
extern "C" {
#define BLOOM_EXTRA_NOEXCEPT noexcept
#else
#define BLOOM_EXTRA_NOEXCEPT /* Nothing */
#endif

int bloom_extra_initialize(void) BLOOM_EXTRA_NOEXCEPT;

#ifdef __cplusplus
}
#endif
#endif
