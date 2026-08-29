# Linux Memory-Mapped File Management System

A Linux-based system programming project demonstrating efficient file access and management using memory mapping.

## Team Members

| Roll Number | Name            |
| ----------- | --------------- |
| 2520080013  | D. Sri Varshini |
| 2520080001  | Shreyas Panjala |
| 2520080022  | Ch Karthikeya   |

**Section:** 12
**Team:** 15
**Supervisor:** M. Raghupathi

## Abstract

The **Linux Memory-Mapped File Management System** demonstrates efficient file access using the Linux `mmap()` system call. Instead of repeatedly using `read()` and `write()`, the system maps file contents directly into the process's virtual address space, allowing them to be accessed and modified as memory.

The project demonstrates key Operating Systems concepts including **virtual memory, memory mapping, process address space, memory protection, file management, system calls, and synchronization**.

The system uses Linux system calls such as `open()`, `fstat()`, `mmap()`, `msync()`, `munmap()`, and `close()`.

## Technologies Used

* **Language:** C
* **Operating System:** Linux / Ubuntu
* **Compiler:** GCC
* **APIs:** Linux System Calls / POSIX APIs
* **Version Control:** Git / GitHub

## Setup & Run

### Clone the Repository

```bash
git clone https://github.com/DSriVarshini/OSSP-.git
cd OSSP-/Project
```

### Compile

```bash
gcc *.c -o mmap_manager
```

### Run

```bash
./mmap_manager
```

> The compilation command may vary depending on the final source files.

## Core System Calls

| System Call | Purpose                            |
| ----------- | ---------------------------------- |
| `open()`    | Opens the file                     |
| `fstat()`   | Obtains file size and metadata     |
| `mmap()`    | Maps the file into memory          |
| `msync()`   | Synchronizes changes with the file |
| `munmap()`  | Removes the memory mapping         |
| `close()`   | Closes the file                    |

## Current Status

**Phase: Development**

The project has completed the problem definition, objectives, methodology, technology selection, and module allocation. Implementation and integration of the individual modules are currently in progress.

### Module Responsibilities

* **D. Sri Varshini:** File handling using `open()`, `fstat()`, and `close()`
* **Shreyas Panjala:** Memory mapping using `mmap()` and `munmap()`
* **Ch Karthikeya:** Synchronization using `msync()`, integration, and testing

## Expected Outcome

A functional Linux application that allows users to open, read, modify, synchronize, and safely unmap files using memory mapping and Linux system calls.

## Course Information

**Course:** Operating Systems and Systems Programming
**Course Code:** 25CS2104E
**Academic Year:** 2026–27
**Term:** I
