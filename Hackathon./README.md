# Linux Command Execution Time Profiler

A C program that executes a Linux command and reports:
- Elapsed execution time
- User and system CPU time
- Peak resident memory usage
- Process ID and exit status

## Requirements
Ubuntu/Linux with GCC.

## Compile
```bash
gcc -Wall -Wextra -O2 profiler.c -o profiler
```

## Run
```bash
./profiler sleep 2
./profiler ls -l
./profiler bash -c 'ls -l | wc -l'
```

## Implementation
Uses fork(), execvp(), wait4(), and clock_gettime().
