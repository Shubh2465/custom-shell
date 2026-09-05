# Custom Shell

I have always wanted to apply my Operating Systems knowledge to something I use every day as a developer. This project is my attempt to build a lightweight Unix-like shell from scratch in **C++** while learning how modern shells interact with the Linux kernel.

Instead of recreating an existing shell all at once, I am building it incrementally to understand **process management, POSIX system calls, file descriptors, and operating system internals** through hands-on implementation.

---

## Features

Current implementation supports:

* Execute external commands using `fork()` and `execvp()`
* Wait for child processes using `wait()`
* Built-in `cd` command using `chdir()`
* Interactive command prompt
* Command parsing using C++ `stringstream`
* Basic error handling using `perror()`

---

## Technologies

* C++17
* Linux
* POSIX System Calls

---

## Build

Compile:

```bash
g++ shell.cpp -o myshell
```

Run:

```bash
./myshell
```

---

## Example

```text
One_Peice_Is_Real> pwd
/home/user

One_Peice_Is_Real> ls

One_Peice_Is_Real> echo Hello World
Hello World

One_Peice_Is_Real> cd test

One_Peice_Is_Real> pwd
/home/user/test

One_Peice_Is_Real> exit
```

---

## System Calls Used

| System Call | Purpose                                              |
| ----------- | ---------------------------------------------------- |
| `fork()`    | Create a child process                               |
| `execvp()`  | Replace the child process with the requested program |
| `wait()`    | Wait for child process completion                    |
| `chdir()`   | Change the current working directory                 |
| `perror()`  | Display system error messages                        |

---

## Learning Objectives

This project focuses on understanding:

* Process creation and execution
* Parent-child process relationships
* Built-in shell commands
* Command parsing
* Linux process lifecycle
* POSIX APIs

Future milestones will explore file descriptors, input/output redirection, pipes, inter-process communication, signals, and job control.

---

## Roadmap

* [x] Interactive shell
* [x] Command execution (`fork()` + `execvp()`)
* [x] Built-in `cd`
* [ ] Output redirection (`>`)
* [ ] Input redirection (`<`)
* [ ] Append redirection (`>>`)
* [ ] Pipes (`|`)
* [ ] Background jobs (`&`)
* [ ] Signal handling (`Ctrl+C`)
* [ ] Command history
* [ ] Environment variable expansion
* [ ] Improved command parsing

---

## Project Structure

```text
.
├── shell.cpp
└── README.md
```

---

## Motivation

The goal of this project is **not** to recreate a production-ready shell like Bash. Instead, I want to understand how a shell works internally by implementing each feature from scratch using Linux system calls.

This project serves as a practical extension of my Operating Systems coursework and a way to deepen my understanding of systems programming. My aim is to eventually build a shell that I can use daily while appreciating the low-level concepts that make it work.
