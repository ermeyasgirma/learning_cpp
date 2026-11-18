# Chapter 2 - Functions, Conditionals and Loops

Build: `g++ -std=c++17 -Wall -Wextra -g file.cpp -o file`

---

## Lessons 8-9: Creating Functions, The Call Stack

Covers: `main`, defining and calling functions, the call stack, step into / step over / step out in a debugger.

### Challenge: Call-stack tour
Write `main -> startGame() -> loadLevel() -> spawnEnemy()`, where each function prints its name on entry.

- In gdb, `break spawnEnemy`, `run`, then `backtrace` (`bt`). Match each frame to your source.
- Restart, `break main`, then use `step` (into), `next` (over), and `finish` (out) to reach `spawnEnemy` and back out again.

---

## Lessons 10-11: Conditional Logic, Switch Statements

Covers: `if`/`else if`/`else`, the ternary operator, nested ternaries, `switch`, fallthrough, `break`, `[[fallthrough]]`, `default`.

### Challenge: HTTP status describer
`int code` -> print a description.

1. With `if`/`else if`: 1xx Informational, 2xx Success, 3xx Redirect, 4xx Client error, 5xx Server error, anything else Invalid.
2. With `switch` over specific codes: `200`, `201`, `204` share one message (use fallthrough), `404` and `500` get their own, and `default` covers the rest.
3. Mark one intentional fallthrough with `[[fallthrough]]`. Remove a `break` elsewhere, compile with `-Wimplicit-fallthrough`, and read the warning.
4. One-liner: `std::string label = code < 400 ? "ok" : "error";`. Then extend it with a nested ternary for `>= 500`, and decide whether it's still readable.

---

## Lessons 12-13: Return Statements, Implicit Conversions and Narrowing

Covers: return types, side effects, early returns (including in `void`), multiple returns, `return` vs `cout`, implicit conversions, narrowing, and `{}` preventing narrowing.

### Challenge: Damage calculator
`int calculateDamage(int base, bool isCritical, bool targetIsImmune)`

- Use early returns: immune returns `0` first, critical returns `base * 2`, otherwise return `base`.
- Write a `void logHit(int dmg)` that returns early if `dmg == 0`.
- Narrowing: call it with `calculateDamage(12.9, true, false)` and print the result. Then try `int x{12.9};` and read the error. Add `-Wconversion` and see what else gets flagged.
- Demonstrate `bool` -> `int` and `int` -> `bool` conversions in arithmetic and conditions.

---

## Lessons 14-16: Arguments/Parameters, Scope, Forward Declarations

Covers: parameters vs arguments, multiple and optional (default) parameters, expressions as arguments, global/block/parameter scope, shadowing, function prototypes, circular dependencies.

### Challenge: Mutual recursion
Write `bool isEven(int n)` and `bool isOdd(int n)` that call **each other** (`isEven(0)` is `true`, `isOdd(0)` is `false`). This only compiles with a forward declaration. Put `main` at the top and all definitions below it.

### Challenge: Defaults and shadowing
- `void attack(int damage, int times = 1, bool verbose = false)`: call it with 1, 2, and 3 arguments.
- Declare a global `int health{100}`, then inside a block declare a local `health` and modify it. Print both. Compile with `-Wshadow`.
- Show a variable declared inside an `if` block isn't accessible after it (read the compile error).

---

## Lessons 17-20: Loops, Modulus, Fizz Buzz, Short-circuit Evaluation

Covers: `while`, `do while`, `for`, infinite loops, loop scope, nested loops, `continue`, `%`, the cycle of modulus, `&&`/`||` short-circuiting.

### Challenge: Fizz Buzz, then generalise
1. Classic Fizz Buzz from 1 to 100.
2. Add rule 7 -> "Bazz" without writing an `if` for every combination (hint: build the output up as you go).

### Challenge: Loop sampler
- `for`: print a multiplication table (nested loops) from 1 to 9, using `continue` to skip the diagonal.
- `while`: print the Collatz sequence for a number and count the steps.
- `do while`: a "menu" that prints once and loops while `choice != 0` (hard-code a sequence of choices for now, since input comes in ch11).
- `%` cycle: print the day of the week for days 0..20 using `day % 7`.

### Challenge: Prove short-circuiting
Write `bool check(const char* name, bool result)` that prints `name` and returns `result`. Then evaluate:
```cpp
check("A", false) && check("B", true);
check("A", true)  || check("B", true);
```
Explain which lines print. Then use short-circuiting to guard a division: `if (d != 0 && n / d > 2)`.
