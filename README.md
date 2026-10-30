*This project has been created as part of the 42 curriculum by dgankhuy.*

# ft_printf

## Description

**ft_printf** is a project from the 42 curriculum that aims to recreate the behavior of the standard C library function `printf()`.

The goal of this project is to understand variadic functions in C, manage different data types, and format output using conversion specifiers. Instead of relying on the original `printf()` function, this implementation uses the `write()` system call to display characters and formatted values directly to standard output.

The project produces a static library named `libftprintf.a`, which can be linked to other C programs.

### Supported Conversions

The implementation supports the following conversion specifiers:

| Specifier | Description |
|---|---|
| `%c` | Prints a single character. |
| `%s` | Prints a string. If the string pointer is `NULL`, it prints `(null)`. |
| `%p` | Prints a pointer address in hexadecimal, prefixed with `0x`. A null pointer is printed as `(nil)`. |
| `%d` | Prints a signed decimal integer. |
| `%i` | Prints a signed decimal integer. |
| `%u` | Prints an unsigned decimal integer. |
| `%x` | Prints an unsigned integer in lowercase hexadecimal. |
| `%X` | Prints an unsigned integer in uppercase hexadecimal. |
| `%%` | Prints a literal percent sign. |

The function returns the number of characters written for the supported conversions and ordinary characters.

## Instructions

### Requirements

To compile and use this project, you need:

- A C compiler, such as `cc` or `gcc`.
- `make`.
- `ar`, to create the static library.
- A Unix-like environment with the standard C development tools.

### Compilation

Clone the repository and navigate to the project directory:

```bash
git clone <repository-url> ft_printf
cd ft_printf
```

Compile the library using the provided Makefile:

```bash
make
```

This creates the static library:

```text
libftprintf.a
```

The Makefile uses the following compiler flags:

```text
-Wall -Werror -Wextra
```

These flags enable common compiler warnings and treat warnings as errors.

### Makefile Commands

| Command | Description |
|---|---|
| `make` | Compiles the source files and creates `libftprintf.a`. |
| `make all` | Builds the library. |
| `make clean` | Removes the object files (`.o`). |
| `make fclean` | Removes the object files and the compiled library. |
| `make re` | Performs a full rebuild by cleaning and recompiling the project. |

### Using the Library

Include `ft_printf.h` in your C source file and link your program against `libftprintf.a`.

For example, create a file named `main.c`:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello, %s!\n", "42");
	ft_printf("Character: %c\n", 'A');
	ft_printf("Integer: %d\n", -42);
	ft_printf("Unsigned: %u\n", 42);
	ft_printf("Hexadecimal: %x\n", 255);
	ft_printf("Pointer: %p\n", (void *)main);
	ft_printf("Percentage: %%\n");
	return (0);
}
```

Compile the program:

```bash
cc -Wall -Werror -Wextra main.c -L. -lftprintf -o test
```

Run the executable:

```bash
./test
```

The output will be similar to:

```text
Hello, 42!
Character: A
Integer: -42
Unsigned: 42
Hexadecimal: ff
Pointer: 0x...
Percentage: %
```

The pointer address will vary depending on the execution environment.

**Note:** The example assumes that `main.c` is in the project root, alongside `ft_printf.h` and `libftprintf.a`.

## Algorithm and Data Structures

### 1. General Algorithm

The implementation processes the format string from left to right.

The main function, `ft_printf()`, follows these steps:

1. Initialize a variadic argument list using `va_start()`.
2. Iterate through the format string one character at a time.
3. If the current character is not `%`, write it directly to standard output using `write()`.
4. If a `%` is encountered and another character follows it, interpret the next character as a conversion specifier.
5. Call `con_type()` to dispatch the conversion to the appropriate handler.
6. Print the converted value and accumulate the number of characters written.
7. Finish processing and release the variadic argument list using `va_end()`.
8. Return the accumulated character count.

This approach separates format-string parsing from conversion handling, making the implementation easier to understand and maintain.

### 2. Variadic Functions and Argument Handling

The function uses a variadic parameter:

```c
int ft_printf(const char *conversion, ...);
```

The `...` allows the function to accept a variable number of arguments.

The implementation uses `va_list`, `va_start()`, `va_arg()`, and `va_end()` from `<stdarg.h>` to retrieve these arguments.

Each conversion handler extracts the argument corresponding to its expected type.

For example:

- `%c` retrieves an `int` and converts it to a `char`.
- `%s` retrieves a `char *`.
- `%d` and `%i` retrieve an `int`.
- `%u`, `%x`, and `%X` retrieve an `unsigned int`.
- `%p` retrieves a `void *` and converts it to an integer representation for hexadecimal output.

Using the appropriate argument type is important because variadic functions do not automatically verify that the supplied arguments match the format string.

### 3. Conversion Dispatching

The function `con_type()` determines which conversion handler should process a specifier.

It delegates conversions to the following functions:

| Function | Responsibility |
|---|---|
| `con_c_s()` | Handles characters and strings (`%c`, `%s`). |
| `con_p()` | Handles pointers (`%p`). |
| `con_d_i_u_x()` | Handles decimal, unsigned decimal, and hexadecimal integers (`%d`, `%i`, `%u`, `%x`, `%X`). |
| `put_hex()` | Prints an integer in hexadecimal notation. |
| `print_sign_num()` | Handles the sign of a signed integer before printing its magnitude. |
| `print_num()` | Prints an unsigned integer in decimal notation. |
| `ft_strlen()` | Calculates the length of a null-terminated string. |

The dispatching approach avoids placing all conversion logic inside a single function.

### 4. Recursive Number Conversion

The implementation uses recursion to print decimal and hexadecimal numbers.

#### Decimal Conversion

The function `print_num()` prints an unsigned integer in decimal notation.

If the number is at least 10, the function first calls itself with the number divided by 10. It then prints the remainder of the division by 10 as a character.

For example, to print `123`:

1. The function recursively processes `123 / 10`, producing `12`.
2. It processes `12 / 10`, producing `1`.
3. It prints the digits as the recursive calls return, producing `123` in the correct order.

This approach eliminates the need for a temporary character array to reverse the digits.

#### Signed Integer Conversion

The function `print_sign_num()` handles signed integers.

If the input is negative, it prints the minus sign and converts the magnitude to a positive value before passing it to `print_num()`.

A `long` intermediate variable is used so that negating the minimum value of a typical 32-bit `int` does not overflow the signed `int` type.

#### Hexadecimal Conversion

The function `put_hex()` converts an integer to base 16.

It recursively processes the number divided by 16, then prints the remainder as a hexadecimal digit.

The remainder determines the digit:

- Values from 0 to 9 are represented by `'0'` through `'9'`.
- Values from 10 to 15 are represented by `'a'` through `'f'` for `%x` and `%p`.
- Values from 10 to 15 are represented by `'A'` through `'F'` for `%X`.

For example, the decimal value `255` is printed as `ff` with `%x` and `FF` with `%X`.

For pointer conversions, `con_p()` prints the `0x` prefix before calling `put_hex()`.

### 5. Data Structures

This project does not require complex data structures.

Its main data-handling mechanisms are:

- **`va_list`:** Maintains the state needed to retrieve variadic arguments in sequence.
- **Pointers:** Used to access the format string, retrieve string arguments, and handle pointer conversions.
- **Primitive integer types:** Used to store numbers and perform decimal and hexadecimal calculations.
- **Local variables:** Used to track characters, digits, intermediate values, and the number of characters written.

The implementation does not use linked lists, trees, hash tables, or dynamically allocated data structures.

This is appropriate because the function processes a sequential format string and converts one argument at a time. More complex data structures would add unnecessary overhead.

### 6. Algorithm and Design Justification

The chosen design emphasizes simplicity, modularity, and compatibility with the constraints of a low-level C project.

**Sequential parsing** is suitable because format strings are processed in their original order. Each character can be handled immediately without storing the entire output.

**Conversion dispatching** separates parsing from formatting. Each handler has a clearly defined responsibility, making individual conversions easier to test and debug.

**Recursive number conversion** provides a straightforward way to print digits in the correct order without allocating a temporary buffer. Its call-stack usage is proportional to the number of digits: logarithmic in the magnitude of the input for decimal and hexadecimal conversion.

**Direct output with `write()`** avoids relying on the standard `printf()` implementation and provides low-level control over character output.

**A character counter** allows `ft_printf()` and its handlers to report the number of characters written, which is an important part of `printf()`-style behavior.

Together, these choices produce a small implementation that demonstrates variadic argument handling, base conversion, recursion, and modular C programming.

### 7. Current Implementation Limitations

This implementation focuses on a subset of the standard `printf()` functionality.

- Field widths, precision, flags, and length modifiers are not implemented.
- Unsupported conversion specifiers return zero without producing output for the specifier.
- A trailing `%` at the end of the format string terminates processing.
- Output errors from `write()` are not checked.
- Pointer formatting uses `(nil)` for a null pointer, which may differ from the output expected by a particular `printf()` implementation.
- The implementation is not a complete replacement for every behavior of the standard library's `printf()`.

These limitations should be considered when using the library in other programs.

## Resources

The following references are useful for understanding the concepts used in this project.

### Documentation

- [printf(3) — Linux manual page](https://man7.org/linux/man-pages/man3/printf.3.html): Documents the standard formatted-output function and its conversion specifiers.
- [stdarg(3) — Linux manual page](https://man7.org/linux/man-pages/man3/stdarg.3.html): Explains variadic argument handling with `va_list`, `va_start()`, `va_arg()`, and `va_end()`.
- [write(2) — Linux manual page](https://man7.org/linux/man-pages/man2/write.2.html): Documents the low-level output system call used by this implementation.
- [GNU C Library documentation](https://www.gnu.org/software/libc/manual/): Provides additional information about C library functions and formatted output.
- [GNU Make documentation](https://www.gnu.org/software/make/manual/): Explains Makefiles and automated compilation.

### AI Usage

AI was used as a documentation and learning aid for this project.

Specifically, AI assistance was used to:

- Draft and organize this `README.md` according to the 42 curriculum documentation requirements.
- As a last resort method to have AI explain a concept or syntax where other sources have failed or doesn't exist.

The project source code was inspected to ensure that the documentation reflects the implementation provided in the repository.

## Author

**dgankhuy**

42 Prague student