# bloom

Repository to understand how to create static golang binaries embedding
Measurement Kit. This is basically just an experiment.

## Windows

- install [msys2](http://www.msys2.org/)
- open "MSYS2 MinGW 64-bit"
- `export GOROOT=/mingw64/lib/go`
- `pacman -Syu`
- `pacman -Su mingw-w64-x86_64-gcc mingw-w64-x86_64-go cmake vim make git`
- `git clone https://github.com/bassosimone/bloom`
- `cd bloom`
- `./script/build/mingw`
