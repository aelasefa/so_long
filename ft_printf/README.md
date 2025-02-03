# ft_printf: A Custom `printf` Implementation

## Overview

The **`ft_printf`** project is a recreation of the standard C library's `printf` function. The goal is to implement similar functionality, allowing formatted output while also demonstrating a deep understanding of low-level string handling, memory management, and variadic arguments in C.

This project is part of the **42 Network** curriculum and is aimed at building a strong foundation in C programming.

---

## Introduction

In C, the `printf` function is widely used for formatted output, such as printing variables and literals in different formats. However, its implementation is not trivial. Through this project, we are tasked with replicating `printf` by manually handling format specifiers, flags, field width, precision, and return values. This project enhances our understanding of how functions can accept a variable number of arguments and how format strings are parsed.

---

## Supported Format Specifiers

`ft_printf` supports a variety of format specifiers, just like the original `printf`:

- **%c**: Prints a single character.
- **%s**: Prints a string of characters.
- **%p**: Prints a pointer address.
- **%d / %i**: Prints a decimal (base 10) number.
- **%u**: Prints an unsigned decimal (base 10) number.
- **%x / %X**: Prints a number in hexadecimal (base 16), with `%x` for lowercase and `%X` for uppercase.
- **%%**: Prints a literal percentage symbol.

Example:

```c
ft_printf("Character: %c\n", 'A');        // Output: Character: A
ft_printf("String: %s\n", "Hello World"); // Output: String: Hello World
ft_printf("Pointer: %p\n", &var);         // Output: Pointer: 0x7fffae4
ft_printf("Number: %d\n", 42);            // Output: Number: 42
