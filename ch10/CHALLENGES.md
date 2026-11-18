# Chapter 10 - Clean Code

---

## Lessons 49-50: `auto`, Constants and `const`-Correctness

Covers: `auto` (vs dynamic typing), `auto` return types, `auto` parameters (C++20), `auto*`/`auto&`/`const auto&`, when to use `auto`, `const` variables, `const` member functions, `const` and pointers (all 4 combinations), `const` with `unique_ptr`.

### Challenge: `auto` pitfalls
- `std::vector<Item> inv{...}; for (auto item : inv) item.weight = 0;` doesn't change anything. Fix it with `auto&`. Then use `const auto&` for a read-only loop.
- `auto x = {1};`: find the deduced type (hint: try `x + 1` and read the error).
- `auto Square(int x) { return x * x; }` vs a version with two `return`s of different types. Read the error.
- `auto` parameters: `void Print(auto v)` needs C++20 and g++ 10+. Try it on [Compiler Explorer](https://godbolt.org).

### Challenge: `const` audit
Take your ch9 inventory/monster code and make it `const`-correct:
- Every getter and every member function that doesn't modify state becomes `const`. Call one from a `const Monster&` and fix the errors that come up.
- Every function parameter that's read-only becomes `const&` (for large types) or plain by-value.
- Write and explain all four:
  ```cpp
  int* p;  const int* p;  int* const p;  const int* const p;
  ```
  For each, show which of `*p = 1;` and `p = &other;` compile.
- `const std::unique_ptr<Monster>` vs `std::unique_ptr<const Monster>`: show what each one prevents.

---

## Lessons 51-52: Effective Comments and Javadoc, Style Guides and Formatting

Covers: TODO/context/complexity comments, structured doc comments (`@param`, `@return`), removing comments through naming, aliases and helper functions, style guides, ClangFormat.

### Challenge: Refactor away the comments
Take this and remove every comment by improving the code instead (better names, a type alias, a helper function, an enum):
```cpp
// returns true if player can enter
bool f(int a, int b, int c) {
  // a = level, b = keys, c = 0 normal 1 hard
  if (c == 1) return a >= 20 && b >= 3; // hard mode
  return a >= 10 && b >= 1;
}
```
Then add a proper `/** @brief ... @param ... @return ... */` doc comment to one public function in your ch7 headers.

### Challenge: ClangFormat
`clang-format` is installed at `~/.local/bin/clang-format`.
- `clang-format --style=Google --dump-config > .clang-format` in the repo root, and tweak `IndentWidth` and `ColumnLimit`.
- Mess up the whitespace in a file, then `clang-format -i file.cpp`.
- Compare `--style=LLVM` and `--style=Google` output with `diff`.

---

## Lessons 53-54: Static Analysis, Attributes

Covers: IDE analysis, CppCheck, compiler warnings as analysis, `[[nodiscard]]`, `[[likely]]`/`[[unlikely]]`, `[[deprecated]]`.

### Challenge: Let the tools find bugs
Write a file with these planted issues: an uninitialised variable, an unused variable, a signed/unsigned comparison in a loop, an out-of-bounds array index, and a memory leak.
- Compile with `-Wall -Wextra -Wpedantic -Wshadow -Wconversion`. Note what it catches.
- Install CppCheck (`sudo apt install cppcheck`) and run `cppcheck --enable=all file.cpp`. Note what it catches that the compiler missed.
- Try `-Werror` and see why teams use it.

### Challenge: Attributes
- `[[nodiscard]] bool Withdraw(int)` on `BankAccount` (ch3). Call it without using the result and read the warning. Also add `[[nodiscard]]` to a factory that returns `unique_ptr`.
- `[[deprecated("use TakeDamage")]] void Hurt(int)`. Call it and read the warning.
- `[[likely]]`/`[[unlikely]]` on the branches of a hot-path `if` (C++20, g++ 9 accepts it with `-std=c++2a`). Write one sentence on why profiling beats guessing here.
