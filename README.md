# astr, compile-time array string

An (opinionated) compile-time string processing library for C++20 and above.

If wanted, the code can easily be adapted to C++17.
Feel free to open an issue if you need help with that.

**There are two use-cases demonstrating what this can be used for.**

## Getting short file names as compile time strings

Reproducible and fix size 'strings' for the `__FILE__` name  at compile time.

The code is related to the blog post ['Compile time string literals processing, but why'](https://a4z.gitlab.io/blog/2023/11/04/Compiletime-string-literals-processing.html), which describes some more details about this feature.

## Getting type names as compile time strings

There are many ways of faking reflections in C++ to get a typename, and there are several more or less famouse library solutions around this.

The code here shows how that actually works, without being a fully fletched 'library'.

There is also enough functionality to get the type name as a compile-time string and doing customizations that this can be used to solve some real world use cases.

## Documentation

For now, please have a look at the files in [the testing directory](./tests/base).

They should be easy to understand and show how to use the code.
