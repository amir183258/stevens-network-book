# Stevens UNIX Network Programming (UNPv1) - Implementations

This repository contains my implementations and code samples written while studying the classic book **Unix Network Programming, Volume 1: The Sockets Networking API** by W. Richard Stevens.

The goal of this project is to master low-level network programming in POSIX/Linux environments, focusing on manual resource management, performance, and a deep understanding of socket APIs.

## Prerequisites and Tools
* **Language:** C / C++
* **Target OS:** Linux / POSIX-compliant OS
* **Build System:** GCC/Clang and Make/CMake
* **APIs Used:** Standard POSIX Sockets (including socket, poll, epoll, select)

## Directory Structure
* `src/`: Executable programs including server and client implementations.
* `lib/`: A progressive rewrite of Stevens' utility library (`unp.h`).

## Getting Started
To compile and run the code (using a sample server as an example):
```bash
# Clone the repository
git clone https://github.com/amir183258/stevens-network-book
cd stevens-network-book

# Build the project
mkdir build
cd build

cmake ..
make
