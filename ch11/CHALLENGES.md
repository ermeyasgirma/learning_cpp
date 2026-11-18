# Chapter 11 - Odds and Ends

Build: `g++ -std=c++17 -Wall -Wextra -g file.cpp -o file`

---

## Lessons 55-56: Random Number Generation, Dates/Times/Durations

Covers: `std::random_device`, seeding, engines (`std::mt19937`), distributions (uniform int/real, normal, bernoulli), reproducibility; chrono durations, literals, `count()`, `duration_cast`, `sleep_for`, clocks, time points, `time_t`, `tm`.

### Challenge: Dice and timing
- A `Dice` class holding an `std::mt19937`, with `int Roll(int sides)` using `std::uniform_int_distribution`.
- Roll 2d6 100,000 times and print a text histogram (one `*` per 1000 rolls). Check the bell curve peaks at 7.
- Constructor `Dice(unsigned seed)`: show that a fixed seed gives the same sequence every run (useful for tests), and `std::random_device{}()` gives a different one.
- A 30% "critical hit" chance with `std::bernoulli_distribution`.
- Time the 100,000 rolls with `std::chrono::steady_clock`, then print the result in ms and µs using `duration_cast`.
- A countdown `3, 2, 1, Go!` using `std::this_thread::sleep_for(1s)` and the `std::chrono_literals` namespace.
- Print today's date by converting `system_clock::now()` -> `time_t` -> `tm` (`localtime_r`).

---

## Lessons 57-58: String Interpolation, Overloading `<<`

Covers: `std::format`, `std::print`, positional args, width/alignment/fill, float precision, formatting custom types; overloading `operator<<`, chaining, serialising objects.

> Your local g++ 9.4 doesn't have `<format>` (it needs g++ 13+). Use [Compiler Explorer](https://godbolt.org) with a recent GCC for the `std::format` parts, or install a newer compiler.

### Challenge: Scoreboard
- Using `std::format`, print a table of players with name left-aligned (width 12), score right-aligned (width 6), and accuracy to 1 decimal place as a percentage:
  ```
  Name           Score  Acc
  Alice            950  87.5%
  Bob               40   3.0%
  ```
- Use positional arguments `{1} {0}` and literal braces `{{}}` somewhere.
- Center a title with a fill character: `{:*^30}`.

### Challenge: `operator<<`
- `std::ostream& operator<<(std::ostream&, const Vector3&)` (ch3) printing `(x, y, z)`. Chain it: `std::cout << a << " + " << b << " = " << a + b;`.
- Do the same for `Monster` using the virtual `Render` (or a virtual `Print(std::ostream&)`) so `std::cout << *monsterPtr` is polymorphic.
- Explain why `operator<<` can't usefully be a member function of `Vector3`.
- Serialise: write a `Player` to a `std::ostringstream` as `name,level,health` and print the string.

---

## Lessons 59-60: System Calls and Terminal Management, User Input

Covers: `system("clear")`, application loops, flickering and double buffering, `std::cin`, `std::getline`.

### Challenge: Robust input
- `int ReadInt(const std::string& prompt, int min, int max)` loops until the user enters a valid integer in range. Handle non-numeric input (`std::cin.fail()`, `clear()`, `ignore()`).
- Read a full name with spaces using `std::getline`. Then reproduce the classic bug of `std::cin >> age;` followed by `getline`, and fix it.

### Challenge: Application loop
- A menu loop: clear the screen, draw a menu, read a choice, act on it, and repeat until Quit.
- Draw a 10x10 grid with a player `@` you move with `w/a/s/d` + Enter. Redraw each frame. Notice any flicker, then build the whole frame into a `std::string` first and print it once (simple double buffering).

---

## Lesson 61: Bitwise Operators and Bit Flags

Covers: fixed-width ints, `std::bitset`, `std::byte`, `|`, `&`, `^`, `~`, bit flags, checking flags.

### Challenge: Permissions
- `enum Permission : uint8_t { Read = 1 << 0, Write = 1 << 1, Execute = 1 << 2, Admin = 1 << 3 };`
- Functions `Grant` (`|=`), `Revoke` (`&= ~`), `Toggle` (`^=`), and `Has` (`&`).
- Print the flag byte with `std::bitset<8>` after each operation.
- Parse a Unix-style string `"rwx"` / `"r-x"` into flags and back.
- `Has(perms, Read | Write)` should mean "has both". Watch out for writing it as `perms & mask` instead of `(perms & mask) == mask`.

---

## Capstone: Terminal dungeon

Combine the whole course into one small multi-file game:

- **ch3/4/6:** `Actor -> Player / Monster -> Goblin / Dragon` with virtual `TakeDamage`/`Render`
- **ch7/8:** split into headers and sources under `namespace Dungeon`, with a `Makefile`
- **ch8:** `enum class GameState { Exploring, Combat, GameOver }` driving a `switch`
- **ch9:** monsters in `std::vector<std::unique_ptr<Monster>>`, with no raw `new`/`delete`
- **ch10:** `const`-correct, formatted with `.clang-format`, and passing `-Wall -Wextra` with no warnings
- **ch11:** seeded RNG for damage and spawns, `ReadInt` for the player's choices, a screen redrawn each turn, `operator<<` for the stats display, and status effects (Poisoned, Stunned, Burning) stored as bit flags

Done when it runs cleanly under `-fsanitize=address,undefined` with no reports.
