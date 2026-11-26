# Philo with a custom allocator

The project-level Makefile delegates builds and tests to the Makefiles in
`philo/` and `malloc/`.

## Build and run

Run these commands from this directory:

```sh
make
./philo/philo 5 800 200 200 2
```

Build the Philo executable linked with the custom allocator:

```sh
make malloc
make philo-malloc
./philo/philo_malloc 5 800 200 200 2
```

Run the Philo integration smoke tests against the custom allocator:

```sh
make philo-test
```

Run the allocator's unit and multithreaded allocation tests on Linux:

```sh
make allocator-test
```

`make test` runs the Philo integration tests. `make clean` removes object
files; `make fclean` also removes generated binaries and libraries.

## Windows and Linux

On Windows, use an MSYS2/MinGW-w64 environment with GCC, GNU Make, and
winpthreads. The same `make`, `make philo-malloc`, and `make philo-test`
commands build Philo with the custom allocator. The allocator uses
`VirtualAlloc`/`VirtualFree` on Windows and `mmap`/`munmap` on Linux.

Philo uses `GetTickCount64`/`Sleep` on Windows and
`clock_gettime`/`nanosleep` on Linux. Windows sleep timing has coarser
granularity, so simulation timings may differ. The allocator's standalone
test harness uses POSIX facilities and is intended to run on Linux.
