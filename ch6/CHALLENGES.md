# Chapter 6 - Polymorphism

Build: `g++ -std=c++17 -Wall -Wextra -g file.cpp -o file`

---

## Lessons 35-36: Function Overloading, Static Casting

Covers: compile-time polymorphism, overloading free and member functions, ambiguous calls, `static_cast`, C-style casts.

### Challenge: Overloaded logger
- `void Log(int)`, `void Log(double)`, `void Log(bool)`, `void Log(const std::string&)`, and `void Log(const Vector3&)` (from ch3). Each prints its type and value.
- Call `Log('a')`, `Log(5.0f)`, and `Log("hello")`. Predict which overload each one picks, then check. `"hello"` is a surprise. Explain why.
- Create a genuine ambiguity by calling `Log(5L)`: `long` converts equally well to `int`, `double`, or `bool`. Read the error and resolve it with `static_cast`.
- Average two `int`s correctly using `static_cast<double>`.
- Write `(int)someDouble` and `static_cast<int>(someDouble)` side by side. Then try casting a `const int*` to `int*` with each. Note which one stops you.

---

## Lessons 37-38: Virtual Functions and Overrides, Downcasting

Covers: run-time polymorphism via base references/pointers, `virtual`, `override`, `final`, early vs late binding, slicing, `static_cast` vs `dynamic_cast` downcasts.

### Challenge: Polymorphic combat
Reuse the `Actor -> Monster -> Goblin/Dragon` hierarchy from ch4.

1. Make `Render()` and `TakeDamage(int)` `virtual`. Mark the subclass versions `override`.
2. Write `void Attack(Monster& target)`. Call it with a `Goblin` and a `Dragon`, and confirm each one's override runs.
3. Remove `virtual` and observe early binding: the base version runs.
4. Misspell an override (`Render() const` vs `Render()`) without `override` and note that it silently doesn't override. Add `override` and see the compiler catch it.
5. **Slicing:** write `void AttackByValue(Monster m)`, call it with a `Dragon`, and explain the output.
6. **Downcasting:** given a `Monster*` that could be either subclass, call `Dragon::BreatheFire()` only when it's actually a `Dragon`:
   - Use `dynamic_cast<Dragon*>` and check for `nullptr`.
   - Then do it wrongly with `static_cast<Dragon*>` on a `Goblin` and run with `-fsanitize=undefined`. Read the report.
   - Explain why `dynamic_cast` needs at least one virtual function (a polymorphic type).
7. Mark `Dragon::Render` `final` and confirm that a subclass `RedDragon` can't override it.
