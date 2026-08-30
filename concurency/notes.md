# Concurrency

Source: https://www.hellointerview.com/learn/low-level-design/concurrency/intro

## What Is Concurrency?

Concurrency means multiple things can make progress during the same time period.

Examples:

- Two users try to book the same seat.
- Multiple threads update the same counter.
- Many requests hit a cache while it is refreshing.

In LLD interviews, concurrency usually means threads inside one process sharing memory.
This is different from system design, where concurrency often happens across servers.

## Why It Matters

Concurrency makes simple code harder because actions can overlap in unexpected ways.
Code that works in normal testing can fail in production because thread execution order is unpredictable.

Interviewers want to see if you can:

- Notice shared state.
- Understand what breaks when threads overlap.
- Pick the right synchronization tool.
- Avoid overcomplicating the design.

## Threads And Shared Memory

A process is an isolated running program with its own memory and resources.
Inside a process, multiple threads can exist.

Each thread has its own:

- Program counter
- Registers
- Stack

Threads in the same process share:

- Heap memory
- Global variables
- Open resources

Because memory is shared, two threads can read and write the same data at the same time.
This is where concurrency bugs come from.

## Why Bugs Happen

Operations that look simple in code are often not atomic.

Example:

```cpp
counter++;
```

This can internally mean:

1. Read `counter`.
2. Add `1`.
3. Write the new value.

If two threads do this together, both may read the same old value and overwrite each other.
The final result depends on timing, so bugs can be nondeterministic and hard to reproduce.

## Common Tools

### Atomics

Atomics provide safe operations on a single variable without using a normal lock.

Use for:

- Counters
- Flags
- Simple stats

Example:

```cpp
#include <atomic>

std::atomic<int> counter = 0;

void increment() {
    counter++;
}
```

Atomics are fast, but they only help with single-variable operations.
If multiple values must change together, use a lock.

### Locks / Mutexes

A lock allows only one thread to enter a critical section at a time.

Use for:

- Protecting shared state
- Check-then-act logic
- Updating multiple fields together

Example:

```cpp
#include <mutex>

std::mutex mtx;
int balance = 0;

void deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    balance += amount;
}
```

### Semaphores

A semaphore allows up to `N` threads to access something at the same time.

Use for:

- Limiting concurrent operations
- Resource limits
- Connection pools

Example:

```cpp
#include <semaphore>

std::counting_semaphore<5> permits(5);

void download() {
    permits.acquire();
    // do work
    permits.release();
}
```

### Condition Variables

Condition variables let a thread wait until some condition becomes true.

Use for:

- Waiting efficiently
- Producer-consumer problems
- Building blocking queues

Example:

```cpp
#include <condition_variable>
#include <mutex>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void waitForReady() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });
}
```

### Blocking Queues

A blocking queue is a thread-safe queue.

Producers add work.
Consumers take work.

If the queue is empty, consumers wait.
If the queue is full, producers wait.

Use for:

- Async processing
- Producer-consumer workflows
- Passing tasks between threads

## Three Problem Types

Most interview concurrency problems fall into three groups.

### 1. Correctness

Correctness problems happen when shared state is updated incorrectly.

Example:

- Two users see one seat available.
- Both try to book it.
- Without synchronization, both bookings may succeed.

Solutions:

- Locks
- Atomics
- Thread confinement

### 2. Coordination

Coordination problems happen when threads need to wait for each other or hand off work.

Example:

- A producer creates tasks.
- Consumers process tasks.
- Consumers should wait when there is no work instead of constantly checking.

Solutions:

- Blocking queues
- Condition variables
- Actors
- Event loops

### 3. Scarcity

Scarcity problems happen when many threads want a limited resource.

Example:

- There are 10 database connections.
- 100 requests arrive.
- Only 10 should use a connection at once.

Solutions:

- Semaphores
- Resource pools
- Rate limits

## LLD Example: Seat Booking

```cpp
#include <mutex>

std::mutex mtx;
int seats = 1;

bool bookSeat() {
    std::lock_guard<std::mutex> lock(mtx);
    if (seats == 0) return false;
    seats--;
    return true;
}
```

Without the lock, two threads might both see one seat available and both book it.
The mutex makes the check and update happen as one protected critical section.

## Quick Rule

When shared state exists, ask:

1. Can two threads update this at the same time?
2. Does one thread need to wait for another?
3. Is there a limited resource that needs controlled access?

These map to correctness, coordination, and scarcity.
