# Chapter 9 - Arrays and Dynamic Memory

Build: `g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined file.cpp -o file`

---

## Lesson 45: Dynamic Arrays using `std::vector`

Covers: dynamic vs static arrays, creating vectors, `[]`/`.at()`, `size()`, `push_back`, `emplace_back`, `erase`, modifying items, storing complex types, passing to functions, iterating.

### Challenge: Inventory
- `struct Item { std::string name; int weight; };`
- `std::vector<Item> inventory;`. Add items with both `push_back(Item{...})` and `emplace_back("Sword", 10)` (the second needs a constructor, or C++20).
- `int TotalWeight(const std::vector<Item>&)`.
- `void RemoveHeavy(std::vector<Item>&, int limit)` removes every item over `limit` using `erase` inside a loop. Get the iterator-invalidation bug first, then fix it (hint: only advance when you don't erase).
- Read `inventory[100]` (UB, which ASan catches) and `inventory.at(100)` (throws). Compare.
- Print `size()` and `capacity()` after each `push_back` from 0 to 20 and spot the growth pattern.
- Pass the vector by value to a function that modifies it and show the caller's copy is unchanged.

---

## Lesson 46: Memory Ownership and Smart Pointers

Covers: dynamic memory, ownership, `std::unique_ptr`, `std::make_unique`, dereferencing, why copies are disallowed, `std::move`.

### Challenge: Owned monsters
- `std::vector<std::unique_ptr<Monster>>` holding `Goblin`s and `Dragon`s from ch6. Iterate and call the virtual `Render()`.
- Give `Monster` a printing destructor. Confirm everything is destroyed when the vector goes out of scope, without any `delete`.
- Try to copy a `unique_ptr` and read the error. Then transfer it with `std::move` and show the source is now `nullptr`.
- Write `std::unique_ptr<Monster> SpawnRandom(int seed)` as a factory that returns ownership.
- Write `void Inspect(const Monster&)` and call it with `*ptr`. Explain why it shouldn't take the `unique_ptr`.

---

## Lesson 47: Copy Constructors and Operators

Covers: subresources, shared resources, copy constructors, deep vs shallow copies, copy assignment, self-assignment, recursive copying, `= delete`.

### Challenge: Player with a `unique_ptr<Sword>`
- `class Player { std::string mName; std::unique_ptr<Sword> mWeapon; };`. Copying it doesn't compile. Read the error.
- Write a **deep-copying** copy constructor using a member initializer list.
- Write a copy assignment operator. Consider both options from the lesson: updating the existing `Sword` or replacing it. Handle `p = p;` (self-assignment).
- Prove the copy is deep: modify the copy's sword and show the original's is unchanged.
- Make a `UniqueToken` class non-copyable with `= delete`.

---

## Lesson 48: Managing Memory Manually

Covers: `new`/`delete`, leaks, RAII, virtual destructors, use-after-free, double free, the Rule of Three, `get()`, constructing from raw pointers, `reset()`.

### Challenge: `IntBuffer` (Rule of Three)
Write a class owning `int* mData` and `size_t mSize`, allocated with `new int[size]`.
1. Write it **without** a copy constructor. Copy it, let both go out of scope, and read ASan's **double free** report.
2. Implement the Rule of Three: destructor, copy constructor (deep copy), and copy assignment (self-assignment safe).
3. Use after free: `delete[]`, then read `mData[0]`. Read the ASan report.
4. Leak: `new` without `delete`. ASan's LeakSanitizer reports it at exit.
5. **Virtual destructor:** `Monster* m = new Dragon; delete m;` with a non-virtual base destructor. Show that `~Dragon` never runs, then fix it.
6. Smart/raw interop: create a `unique_ptr<int>`, pass `.get()` to a function taking `int*`, then `reset(new int{5})` and confirm the old value is freed.

Final step: rewrite `IntBuffer` using `std::vector<int>` (or `std::unique_ptr<int[]>`) and delete all three special member functions you wrote. That's the Rule of Zero.
