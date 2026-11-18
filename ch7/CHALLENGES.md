# Chapter 7 - The Preprocessor and the Linker

---

## Lesson 39: Preprocessor Definitions

Covers: translation units, directives, conditional inclusion (`#ifdef`/`#if`), setting definitions from the build, `#define`, text-replacement and function-like macros.

### Challenge: Build-time switches
- Write a `LOG(msg)` macro that prints `[file:line] msg` (using `__FILE__` and `__LINE__`) only when `DEBUG` is defined. Otherwise it expands to nothing.
- Build twice: `g++ -DDEBUG main.cpp` and `g++ main.cpp`. Confirm the log lines disappear.
- Run `g++ -E main.cpp | tail -40` to look at the preprocessed output in both builds.
- Write the classic broken macro `#define SQUARE(x) x * x`, show that `SQUARE(1 + 2)` gives `5`, fix it with parentheses, and then show that `SQUARE(i++)` is still broken.
- Use `#if VERSION >= 2` with `-DVERSION=2` to switch between two implementations of a function.

---

## Lessons 40-41: The `#include` Directive, Header Files

Covers: `<>` vs `""`, include directories, redefinition errors, header guards and `#pragma once`, declaration vs definition, multiple source files, header-only code, why not to `#include` a `.cpp`, linking, incomplete types.

### Challenge: Split a project
Take the ch6 monster hierarchy and split it into:
```
ch7/
  include/Actor.h    Monster.h    Dragon.h    Goblin.h
  src/Actor.cpp      Monster.cpp  Dragon.cpp  Goblin.cpp  main.cpp
```
Build: `g++ -std=c++17 -Iinclude src/*.cpp -o game`

Break things on purpose and read each error:
1. **Missing header guard:** have both `Dragon.h` and `Goblin.h` include `Monster.h`, and include both in `main.cpp`. You get a redefinition error. Fix it with `#ifndef` guards in one header and `#pragma once` in another.
2. **Undefined reference:** leave `Dragon.cpp` out of the build command. Note that it's the **linker** that complains, not the compiler.
3. **Multiple definition:** define a non-inline free function in a header included by two `.cpp` files. Fix it by moving the definition to a `.cpp`, or by marking it `inline`.
4. **Including a `.cpp`:** `#include "Dragon.cpp"` in `main.cpp` while also compiling `Dragon.cpp`. Explain the error.
5. **Incomplete type:** in `Actor.h`, forward-declare `class Weapon;` and hold a `Weapon*`. Show it compiles without including `Weapon.h`. Then try holding a `Weapon` by value and read the error.
6. **Separate compilation:** compile each `.cpp` to `.o` with `-c`, then link them. Change one `.cpp` and rebuild only that object.

Stretch: write a 10-line `Makefile` for this.
