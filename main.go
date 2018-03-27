package main

/*
#cgo CFLAGS: -I.
#cgo darwin LDFLAGS: -L./bloom_core -L./bloom_extra -lbloom_core -lbloom_extra -lc++
#cgo linux LDFLAGS: -L./bloom_core -L./bloom_extra -lbloom_core -lbloom_extra -lstdc++
#cgo windows LDFLAGS: -L./bloom_core -L./bloom_extra -lbloom_core -lbloom_extra -lstdc++ -static

#include "bloom_core/core.h"
#include "bloom_extra/extra.h"
*/
import "C"

func main() {
	C.bloom_core_initialize()
	C.bloom_extra_initialize()
}
