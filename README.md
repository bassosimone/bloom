# bloom

We are leaning towards shipping [GOONI](https://github.com/OpenObservatory/gooni), a [Go](https://golang.org/) based command line interface for OONI.

Since golang only uses static linking, we need to figure out how to statically link MK in gooni.

Ideally, the build process should not be paintful. Possibly, it should be possible to do all the development from macOS.

What we need to achieve is basically the following:

1. compile MK and all its dependencies using `-fPIC` or equivalent to obtain static libraries;
2. statically link such libraries in GOONI using [cgo](https://golang.org/cmd/cgo/).

This seems simple, right? But actually it's not super simple. So, I created this toy repository with a couple of dummy libraries, one in C (`bloom_core`) and one in C++14 (`bloom_extra`), to investigate more easily.

## The gold standard

It is important to understand exactly what we want to obtain when we discuss static linking. We agreed with [@hellais](https://github.com/hellais) that looking at what the [Docker](https://www.docker.com/) client links, because Docker is written in Go and links some C code.

### Linux

```
$ ldd `which docker`
linux-vdso.so.1 =>  (0x00007fffe02c9000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fc2b0b30000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fc2b0760000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fc2b0e00000)
````

### macOS

```
$ otool -L `which docker`
/usr/local/bin/docker:
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1225.1.1)
	/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation 
	    (compatibility version 150.0.0, current version 1253.0.0)
	/System/Library/Frameworks/Security.framework/Versions/A/Security
	    (compatibility version 1.0.0, current version 57336.1.9)
```

### Windows

Docker does not install on my Windows system because it's not cool enough.

```
...
```

## What we can achieve "easily"

With "easily" I mean what corresponds to [e6a88355](
https://github.com/bassosimone/bloom/tree/e6a88355f3e69da41fcece508653f21f17a99cfb).

### Linux

Assuming you have gcc, g++, libstdc++, cmake, make, and go installed, you can
run `./script/build/linux`. The script will also print dependencies:

```
    [snip]
+ ldd ./bloom
	linux-vdso.so.1 =>  (0x00007fffc80e2000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fb3b5490000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fb3b5270000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fb3b5050000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fb3b4c70000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fb3b5a00000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fb3b4960000)
    [snip]
```

### macOS

Assuming you have Xcode command line tools, cmake, and go installed, you can
run `./script/build/darwin`. The script will also print dependencies:

```
$ ./script/build/darwin
    [snip]
+ otool -L ./bloom
./bloom:
	/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 400.9.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1252.0.0)
    [snip]
```

### Windows using msys2

This solution requires Windows (no cross build on macOS). The build procedure
(only tested for Windows 64) looks like this:

- install [msys2](http://www.msys2.org/)
- open "MSYS2 MinGW 64-bit" and type the following inside the shell

```
export GOROOT=/mingw64/lib/go
pacman -Syu
```

After this step, the shell may exit (it occurred to me) and you need to start
another shell and continue typing:

```
pacman -Su mingw-w64-x86_64-gcc mingw-w64-x86_64-go cmake vim make git
git clone https://github.com/bassosimone/bloom
cd bloom
./script/build/mingw
```

The script output will be:

```
    [snip]
+ ldd ./bloom.exe
	ntdll.dll => /c/WINDOWS/SYSTEM32/ntdll.dll (0x7ffe73b70000)
	KERNEL32.DLL => /c/WINDOWS/System32/KERNEL32.DLL (0x7ffe73240000)
	KERNELBASE.dll => /c/WINDOWS/System32/KERNELBASE.dll (0x7ffe70c50000)
	msvcrt.dll => /c/WINDOWS/System32/msvcrt.dll (0x7ffe73570000)
	WS2_32.dll => /c/WINDOWS/System32/WS2_32.dll (0x7ffe73740000)
	RPCRT4.dll => /c/WINDOWS/System32/RPCRT4.dll (0x7ffe73120000)
	WINMM.dll => /c/WINDOWS/SYSTEM32/WINMM.dll (0x7ffe6dda0000)
	winmmbase.dll => /c/WINDOWS/SYSTEM32/winmmbase.dll (0x7ffe6dc60000)
	??? => ??? (0x180000)
	??? => ??? (0x150000)
	cfgmgr32.dll => /c/WINDOWS/System32/cfgmgr32.dll (0x7ffe703b0000)
	ucrtbase.dll => /c/WINDOWS/System32/ucrtbase.dll (0x7ffe70400000)
    [snip]
```
