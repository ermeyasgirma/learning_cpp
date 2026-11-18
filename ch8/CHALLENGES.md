# Chapter 8 - Namespaces and Enums

Build: `g++ -std=c++17 -Wall -Wextra -g file.cpp -o file`

---

## Lesson 42: Namespaces

Covers: creating and accessing namespaces, `::`, nested namespaces, namespaces vs classes, the ODR, `extern`, `inline`, reopening namespaces, anonymous namespaces.

### Challenge: Organise the game
Using the multi-file layout from ch7:
- Put everything in `namespace Game`, with `Game::Entities` (Actor/Monster/...) and `Game::Utils` (logging/helpers). Use C++17 nested syntax: `namespace Game::Utils { ... }`.
- Reopen `Game::Utils` in a second file to add another function.
- Put a helper in an **anonymous namespace** in one `.cpp`. Define a helper with the same name in another `.cpp` and show there's no linker clash. Then remove the anonymous namespace and get the "multiple definition" error.
- Share a global counter across files: `extern int gMonsterCount;` in the header, and the definition in exactly one `.cpp`. Then replace it with `inline int gMonsterCount{0};` in the header (C++17) and explain the difference.
- Give two namespaces a `Log()` function and call each one explicitly.

---

## Lesson 43: Enums

Covers: defining and using `enum class`, the advantages over strings and ints, comparing strings.

### Challenge: Enum state machine
- `enum class TrafficLight { Red, Green, Yellow };`
- `TrafficLight Next(TrafficLight)` uses a `switch` with no `default`. Compile with `-Wall`, then add a `Flashing` state and see the `-Wswitch` warning tell you which case is missing.
- `std::string ToString(TrafficLight)`.
- Run the cycle 7 times from `Red`.
- Show that `TrafficLight::Red == 0` doesn't compile but a plain `enum` would allow it. Get the underlying value with `static_cast<int>`.
- Replace a string-based `std::string state = "red";` check with the enum and explain which typo bugs disappear.

---

## Lesson 44: The `using` Keyword

Covers: `using namespace`, `using` declarations for specific names, scoped `using`, literal namespaces, `using enum` (C++20), type aliases, `typedef`.

### Challenge: Aliases and scoped `using`
- Inside a single function, `using Game::Utils::Log;`. Show it isn't visible in another function.
- `using namespace std::string_literals;` then `auto s = "hi"s;`. Print the type difference from `"hi"` (compare `sizeof`, or call an overloaded `Log` from ch6).
- `using Health = int;` and `using MonsterList = std::vector<Game::Entities::Monster*>;`. Write the same aliases with `typedef` and decide which reads better.
- Use an alias to switch a type at compile time: `using Real = float;` vs `double`, controlled by `#ifdef HIGH_PRECISION`.
- `using enum TrafficLight;` inside a `switch` needs C++20 and **g++ 10+**. Your local g++ 9.4 will reject it, so try it on [Compiler Explorer](https://godbolt.org) instead.
- Write one sentence on why `using namespace std;` in a header is a bad idea.
