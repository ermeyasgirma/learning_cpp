# Chapter 5 - Memory, References and Pointers

Build: `g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined file.cpp -o file`

---

## Lesson 31: References

Covers: pass by value vs reference, output parameters, `const&`, references must be initialised and can't be reseated, references as class members, returning references.

### Challenge: Three swaps
- `void swapByValue(int a, int b)`: show that it doesn't work.
- `void swapByRef(int& a, int& b)`: show that it does.
- `void heal(const Player& p)`: try to modify `p` and read the error.
- `bool tryParseDigit(char c, int& out)`: an **output parameter** that returns success and writes into `out`.
- Pass a large struct (with a `std::string` member and a big `int` array) by value vs by `const&` in a loop that runs 1 million times. Time it roughly with `time ./prog` and compare.
- Show that `int& r = a; r = b;` assigns `b` to `a` rather than rebinding `r`. Print `&r`, `&a`, `&b`.

---

## Lesson 32: Pointers

Covers: `&` (address-of), `*` (dereference), pointers vs references, precedence, `->`, `nullptr`.

### Challenge: Pointer basics
- Write `swapByPtr(int* a, int* b)`, plus a version that safely handles `nullptr` arguments.
- Point to a `Player`. Access a member with both `(*p).health` and `p->health`.
- Write a function `Player* findWeakest(Player* a, Player* b, Player* c)` that returns the one with the lowest health, or `nullptr` if all are null.
- Precedence: explain the difference between `*p.health` (compile error) and `(*p).health`, and between `*p++` and `(*p)++`.
- Show one thing a pointer can do that a reference can't (reseating, or being null).

---

## Lesson 33: The `this` Pointer

Covers: dereferencing `this`, identifying the caller, chaining, operators returning `*this`, prefix vs postfix operators.

### Challenge: Fluent builder and counters
- `CharacterBuilder` with `SetName`, `SetLevel`, and `SetClass`, each returning `CharacterBuilder&` (`return *this;`), so you can write `b.SetName("A").SetLevel(5).SetClass("Mage");`.
- Change one setter to return by value instead of by reference and show that the chain stops modifying the original.
- Give `Vector3` (ch3) `-=` as a member function returning `*this`.
- Give a `Counter` class prefix `++c` (returns `Counter&`) and postfix `c++` (takes `int`, returns the old value by copy). Explain why prefix is preferred.
- Write `bool IsSameAs(const Counter& other) const { return this == &other; }`.

---

## Lesson 34: Dangling Pointers and References

Covers: stack memory, local variable lifetimes, returning pointers/references to locals, storage durations.

### Challenge: Break it on purpose
Write three dangling bugs, run each with ASan (`-fsanitize=address`), and read the report:
1. `int& getRef() { int x{5}; return x; }`
2. `int* getPtr() { int x{5}; return &x; }`
3. A pointer to a variable from an inner `{}` block, used after the block ends.

For each: note what the compiler warned about (if anything) compared with what ASan caught at runtime. Then fix each one in two different ways: return by value, and use `static` storage duration. Explain the trade-off of using `static`.
