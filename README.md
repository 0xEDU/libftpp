# libftpp

**Further Exploration into Advanced C++**

Welcome to **libftpp** – a powerful and modern C++ toolbox without any dependency on external libraries.

## 🛠 Features

- 📦 A modular and extensible architecture
- 🧵 Thread-safe containers and utilities
- 🔁 Custom implementations of commonly-used design patterns
- 🌐 High-level abstractions for network programming
- 🧮 Tailored math utilities and random generators
- 📚 Zero reliance on external libraries — everything is built from the ground up

## 📦 Project Structure

```bash
libftpp/
├── include/        # Header files for public APIs
├── sources/            # Core library source code, each class in its own file
├── tests/          # Integration tests for the library
└── Makefile        # Build system
```

## 🛠 Requirements
- C++20 or later
- POSIX-compliant system (Linux, macOS, etc.)
- GNU Make

## 🔧 Build Instructions

To build the library, simply run:

```bash
make
```
This will compile the library into a static library file named `libftpp.a`.


## 🧪 Running tests
To run the tests, execute the following command:

```bash
make test
```

This will compile the mains in the `tests/` directory and link them against the `libftpp.a` library. The resulting executables will be placed in the `bin/` directory.


