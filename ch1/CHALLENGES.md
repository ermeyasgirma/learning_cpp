# Chapter 1 - Types and Variables

Build: `g++ -std=c++17 -Wall -Wextra -g file.cpp -o file`

---

## Lessons 1-3: Setup, Objects/Variables/Types, Creating Variables

Covers: hello world, `<<` chaining, `std::endl` vs `\n`, `int`/`float`/`double`/`bool`/`std::string`, the ways to initialise a variable, copying variables, comments, and common compiler errors.

### Challenge: Character sheet
Write a program that declares a character's `name` (`std::string`), `level` (`int`), `health` (`float`), `isAlive` (`bool`) and prints them on one line with a **single** chained `std::cout` statement.

- Initialise each variable a different way: `=`, `()`, `{}`, and declare-then-assign.
- Copy `level` into a new variable, change the copy, and print both to show they're independent.
- Print `isAlive` once as-is and once with `std::boolalpha`.

### Challenge: Read the compiler
Deliberately trigger each error the lesson names: use of an undeclared identifier, redefinition of a variable, and a missing `;`. Compile each one, read the message, and fix it. Note which line the compiler reports compared with where the mistake actually is.

---

## Lesson 4: Numbers

Covers: arithmetic operators, precedence, `++`/`--` (prefix and postfix), compound assignment, unary minus, integer division, floating-point numbers, digit separators (`1'000'000`).

### Challenge: Unit converter
Given `int totalSeconds = 1'000'000;`, print it as days, hours, minutes, and seconds using only `/`, `-`, and `*` (`%` hasn't been covered yet).

- Then print the average of `7` and `2` three ways: `(7 + 2) / 2`, `(7 + 2) / 2.0`, `(7.0 + 2) / 2`. Explain each result.
- Predict and then check the output of: `int x{5}; int a = x++ + ++x;` Why is this a bad idea? Hint: compile with `-Wall`.

---

## Lesson 5: Booleans

Covers: comparison operators, `!`, `&&`, `||`, compound booleans, the "not repeating the variable name" mistake, why `20` is truthy, operator precedence, `&` vs `&&`.

### Challenge: Eligibility checker
With `int age`, `bool hasLicence`, `bool isSuspended`, compute `bool canDrive` meaning *age 17 or older, has a licence, and not suspended*. Print it for 4 hand-picked cases.

- Write the buggy version `age > 17 || 18` and explain why it's always `true`.
- Write `isTeen` as `13 <= age <= 19` (a common bug). Show a value where it gives the wrong answer, then fix it.
- Remove the parentheses from `(a || b) && c` and find inputs where the result changes.

---

## Lesson 6: Types and Literals

Covers: memory and integer width, fixed-width integers (`<cstdint>`), overflow, signed vs unsigned, why unsigned is problematic, compiler warnings, float width, literal suffixes.

### Challenge: Type explorer
1. Print `sizeof` for `char`, `short`, `int`, `long`, `long long`, `float`, `double`, `int8_t`, `int32_t`, `int64_t`.
2. Use `std::numeric_limits<T>::max()` / `min()` to print the range of `int` and `uint8_t`. Print `uint8_t` with `+value` and explain why `+` is needed.
3. Overflow: add 1 to `std::numeric_limits<unsigned int>::max()` (it wraps around, which is well defined). Then do the same with `int` (undefined behaviour). Rebuild with `-fsanitize=undefined` and read the runtime report.
4. Unsigned trap: `unsigned int a{3}; unsigned int b{5}; std::cout << a - b;` Explain the output.
5. Literals: print `0.1f + 0.2f == 0.3f` and `0.1 + 0.2 == 0.3`, then print `0.1 + 0.2` with `std::setprecision(17)`. Explain the result.

Stretch: compile with `-Wall -Wextra -Wconversion -Wsign-conversion` and fix every warning.

---

## Lesson 7: Introduction to Debugging

Covers: build time vs run time, breakpoints, step over, continue.

### Challenge: Find the bug with gdb only
Write (or ask someone else to write) a ~20-line program that computes a running total of health after a sequence of damage/heal events, and plant one wrong operator in it. Without adding any `cout`:

```
gdb ./prog
break main
run
next            # step line by line
print health    # inspect values
continue
```

Find the line where the value first goes wrong. Then set a breakpoint on that line number (`break 14`) and get there directly with `continue`.
