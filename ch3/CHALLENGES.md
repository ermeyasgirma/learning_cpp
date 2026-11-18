# Chapter 3 - Classes and Structs

Build: `g++ -std=c++17 -Wall -Wextra -g file.cpp -o file`

---

## Lessons 21-22: Abstraction and Classes, Encapsulation and Access Specifiers

Covers: user-defined types, classes vs objects, member variables/functions, `.` access, member function prototypes, class invariants, `public`/`private`, getters/setters.

### Challenge: `BankAccount`
- Private `mBalance` (int, in pennies) and `mOwner`.
- Public `Deposit(int)`, `Withdraw(int)`, `GetBalance()`, `GetOwner()`.
- **Invariant:** the balance never goes negative, and deposits/withdrawals must be positive. Reject bad calls (print an error and return `false`).
- Declare the member functions inside the class and define them below it (`bool BankAccount::Withdraw(int amount) { ... }`).
- From `main`, try `account.mBalance = -100;` and read the compile error.
- Decide whether a `SetBalance` setter should exist. Write one sentence on why or why not.

---

## Lesson 23: Constructors and Destructors

Covers: constructor parameters, member initializer lists, multiple constructors, ambiguous calls, default constructor, non-public constructors, destructors.

### Challenge: Lifetime logger
Write a `Tracer` class whose constructor prints `"+ <name>"` and whose destructor prints `"- <name>"`.

- Create tracers in `main`, inside a nested `{}` block, and inside a function. Predict the output order before running it.
- Give `Tracer` a default constructor (name `"anon"`) and a `Tracer(std::string name)` constructor. Then add `Tracer(const char*)` and see whether `Tracer t{"x"};` becomes ambiguous.
- Add a `BankAccount(std::string owner, int initial)` constructor that enforces the invariant from the previous challenge (clamp or reject a negative initial balance).

---

## Lessons 24-26: Structs and Aggregate Initialization, Operator Overloading, Structured Binding

Covers: structs vs classes (technical and semantic), aggregate initialization, operators as functions, free vs member operators, operand order, unary operators, chaining, `auto [x, y, z]`.

### Challenge: `Vector3`
- `struct Vector3 { float x, y, z; };`, created with aggregate initialization `Vector3 v{1, 2, 3};`.
- Overload:
  - `+` and `-` (free functions, taking `const Vector3&`)
  - `*` with a scalar on **both** sides (`v * 2` and `2 * v`, which need two overloads because operand order matters)
  - `==`
  - unary `-`
  - `+=` as a member function returning `Vector3&` so that `a += b += c` chains
- Unpack with `auto [x, y, z] = a + b;` and print each value.
- Swap the names (`auto [z, y, x] = v;`) and confirm the binding is positional, not by name.
- Explain in one sentence why `Vector3` is a struct while `BankAccount` is a class.
