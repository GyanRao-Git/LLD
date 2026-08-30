# Concurrency: Correctness

Sources:

- https://www.hellointerview.com/learn/low-level-design/concurrency/correctness
- https://en.cppreference.com/w/cpp/thread/mutex
- https://en.cppreference.com/w/cpp/atomic/atomic
- https://en.cppreference.com/w/cpp/thread/shared_mutex

Note: the Hello Interview page becomes premium after the intro/outline. These are original notes based on the public preview and standard C++ concurrency concepts.

## Meaning

Correctness means shared data stays valid even when multiple threads access it at the same time.

The main danger is not that the program crashes. The bigger danger is that it silently produces wrong data.

Examples:

- Two users book the same seat.
- A counter misses increments.
- A bank account loses deposits.
- A cache stores inconsistent metadata.

## Core Problem

Concurrency breaks when a thread makes a decision using data that another thread can change before the first thread acts.

Example:

```cpp
if (seats > 0) {
    seats--;
}
```

This looks safe, but it is not.

Two threads can both read `seats = 1`, both enter the `if`, and both book the same seat.

This is called a **check-then-act** bug.

## Critical Section

A critical section is the part of code that reads or modifies shared state.

For seat booking, this whole block must be protected:

```cpp
if (seats > 0) {
    seats--;
}
```

The check and update must happen together.

## Solution 1: Coarse-Grained Locking

Use one lock to protect all related state.

```cpp
#include <mutex>

class SeatBooking {
private:
    std::mutex mtx;
    int seats = 1;

public:
    bool bookSeat() {
        std::lock_guard<std::mutex> lock(mtx);

        if (seats == 0) return false;
        seats--;
        return true;
    }
};
```

Pros:

- Simple
- Easy to reason about
- Good default in interviews

Cons:

- Less parallelism
- One slow operation can block others

Use this first unless performance clearly requires something more advanced.

## Solution 2: Fine-Grained Locking

Use separate locks for independent pieces of state.

Example: each seat has its own lock.

```cpp
#include <mutex>
#include <unordered_map>

class Seat {
public:
    std::mutex mtx;
    bool booked = false;
};

class SeatBooking {
private:
    std::unordered_map<int, Seat> seats;

public:
    bool bookSeat(int seatId) {
        Seat& seat = seats[seatId];
        std::lock_guard<std::mutex> lock(seat.mtx);

        if (seat.booked) return false;
        seat.booked = true;
        return true;
    }
};
```

Pros:

- More concurrency
- Different seats can be booked at the same time

Cons:

- More complex
- Easier to create deadlocks
- Harder to maintain invariants across multiple objects

Use this when independent resources can be protected separately.

## Solution 3: Read-Write Lock

Use a read-write lock when many threads read, but few threads write.

In C++, this is `std::shared_mutex`.

```cpp
#include <shared_mutex>
#include <unordered_set>

class SeatStore {
private:
    mutable std::shared_mutex mtx;
    std::unordered_set<int> bookedSeats;

public:
    bool isBooked(int seatId) const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return bookedSeats.count(seatId) > 0;
    }

    bool book(int seatId) {
        std::unique_lock<std::shared_mutex> lock(mtx);

        if (bookedSeats.count(seatId) > 0) return false;
        bookedSeats.insert(seatId);
        return true;
    }
};
```

Multiple readers can run together.
Writers still need exclusive access.

Use this when reads are very common and writes are rare.

## Solution 4: Atomic Variables

Atomics make operations on a single variable thread-safe.

```cpp
#include <atomic>

std::atomic<int> counter = 0;

void increment() {
    counter++;
}
```

Good for:

- Counters
- Flags
- Simple state

Not good for:

- Multiple related variables
- Check-then-act logic
- Complex invariants

Example problem:

```cpp
std::atomic<int> seats = 1;

bool bookSeat() {
    if (seats > 0) {
        seats--;
        return true;
    }
    return false;
}
```

Even though `seats` is atomic, the whole check-then-act sequence is not atomic.

Better:

```cpp
bool bookSeat() {
    int expected = seats.load();

    while (expected > 0) {
        if (seats.compare_exchange_weak(expected, expected - 1)) {
            return true;
        }
    }

    return false;
}
```

For interviews, prefer a mutex unless atomics are clearly enough.

## Solution 5: Thread Confinement

Thread confinement means only one thread owns and modifies some state.

Instead of many threads touching shared data, other threads send requests to the owner thread.

Example idea:

```text
Many request threads -> booking queue -> single booking worker
```

Pros:

- Avoids shared-memory bugs
- Easy to reason about
- Good for actor/event-loop style designs

Cons:

- Can become a bottleneck
- Requires queueing and message passing

Use this when one component can own the state completely.

## Common Bug 1: Check-Then-Act

Pattern:

```cpp
if (condition_is_true) {
    perform_action();
}
```

Bug:

The condition can change before the action happens.

Examples:

- If seat is free, book it.
- If user has balance, withdraw money.
- If cache has space, insert item.
- If connection is free, assign it.

Fix:

Protect the check and action with the same lock.

## Common Bug 2: Read-Modify-Write

Pattern:

```cpp
x = x + 1;
```

Bug:

This is really read, modify, then write.
Two threads can read the same old value and overwrite each other.

Fix:

Use a lock or atomic operation.

```cpp
std::atomic<int> count = 0;

void add() {
    count.fetch_add(1);
}
```

## Interview Rule

When you see shared state, ask:

1. Can two threads read and write this together?
2. Does a check need to stay true until the action finishes?
3. Are multiple variables part of one invariant?
4. Would one lock be enough to explain the design clearly?

Start simple with a coarse-grained lock.
Move to fine-grained locks, read-write locks, atomics, or thread confinement only when the tradeoff is worth it.
