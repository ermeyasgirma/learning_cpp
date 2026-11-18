# Chapter 4 - Inheritance

Build: `g++ -std=c++17 -Wall -Wextra -g file.cpp -o file`

---

## Lessons 27-28: Inheritance, Protected Class Members

Covers: base and derived classes, public/private inheritance, multiple layers, `final`, `protected`.

### Challenge: Monster hierarchy
```
Actor            (name, Render())
└── Monster      (protected: mHealth; TakeDamage(int))
    ├── Goblin   (final)
    └── Dragon   (BreatheFire())
```
- `Actor::Render()` prints the name. Every subclass gets it for free.
- `mHealth` is `protected`. Show that `Dragon` can modify it but `main` can't (read the compile error).
- Try to inherit from `Goblin` and read the `final` error.
- Change `Dragon` to `class Dragon : private Monster` and see which calls in `main` stop compiling. Then change it back.

---

## Lesson 29: Member Initializer Lists

Covers: syntax, performance, readability, cases where they're required, expressions and parameters in the list.

### Challenge: Initialise what can't be assigned
Give `Monster` a `const int mMaxHealth` and a `std::string& mLogTarget` (a reference). Show that assigning them in the constructor body fails to compile, then fix it with a member initializer list.

- Initialise `mHealth` from an expression using another parameter: `mHealth{maxHealth / 2}`.
- Declare members in the order `mHealth, mMaxHealth` but initialise `mHealth` from `mMaxHealth`. Compile with `-Wall` and read the `-Wreorder` warning. Explain the uninitialised value you get.

---

## Lesson 30: Working with Inherited Members

Covers: calling base constructors, constructor call order, shadowing inherited variables and functions, extending inherited functions.

### Challenge: Constructor chain
- Give `Actor`, `Monster`, and `Dragon` constructors and destructors that print. Build a `Dragon` and confirm the order: base constructors run first, destructors run in reverse.
- `Dragon(std::string name)` must call `Monster(name, 500)`, which calls `Actor(name)`.
- **Shadowing bug:** declare another `int mHealth` in `Dragon`. Show that `TakeDamage` (defined in `Monster`) updates a different variable from the one `Dragon` prints. Then remove it.
- **Extend, don't replace:** `Dragon::Render()` calls `Monster::Render()` (or `Actor::Render()`) and then prints `" (breathes fire)"`.
