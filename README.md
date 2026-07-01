# Codexion

> *This project was developed as part of the 42 School curriculum by **hamezoua**.*

## Overview

**Codexion** is a high-performance concurrent simulation project designed to explore advanced concepts in systems programming, including multithreading, synchronization, resource arbitration, and deterministic execution under strict timing constraints.

The project simulates a high-pressure software development environment where multiple **Coders** (implemented as POSIX threads) compete for a limited set of shared resources called **Dongles**. Each coder repeatedly cycles through several states:

* **Compiling**
* **Debugging**
* **Refactoring**

To survive, a coder must start a compilation within a predefined `time_to_burnout` interval. Failure to do so results in a **burnout event**, immediately terminating the entire simulation.

The primary objective of Codexion is to build a robust concurrent system capable of:

* Preventing race conditions
* Avoiding deadlocks
* Minimizing starvation
* Managing precise timing constraints
* Ensuring deterministic resource scheduling
* Performing a clean and safe shutdown of all threads

---

## Features

* POSIX Threads (`pthread`) based concurrent simulation
* Thread-safe resource management
* Deadlock prevention mechanisms
* Starvation avoidance strategies
* Configurable scheduling policies (`FIFO`, `EDF`)
* Precise timing control in milliseconds
* Resource cooldown management
* Dedicated monitoring thread
* Atomic logging system
* Graceful simulation termination

---

## Compilation

The project follows the **42 School Norm** and compiles with strict compiler flags:

```bash
-Wall -Wextra -Werror
```

Build the project using:

```bash
make
```

---

## Usage

### Syntax

```bash
./codexion \
<number_of_coders> \
<time_to_burnout> \
<time_to_compile> \
<time_to_debug> \
<time_to_refactor> \
[number_of_compiles_required] \
[dongle_cooldown] \
[scheduling_policy]
```

### Parameters

| Parameter                                  | Description                                                          |
| ------------------------------------------ | -------------------------------------------------------------------- |
| `number_of_coders`                         | Total number of coder threads                                        |
| `time_to_burnout`                          | Maximum time (ms) a coder can survive without starting a compilation |
| `time_to_compile`                          | Duration (ms) required to complete a compilation                     |
| `time_to_debug`                            | Time (ms) spent debugging                                            |
| `time_to_refactor`                         | Time (ms) spent refactoring                                          |
| `number_of_compiles_required` *(optional)* | Number of successful compilations required per coder                 |
| `dongle_cooldown` *(optional)*             | Cooldown period (ms) after a dongle is released                      |
| `scheduling_policy` *(optional)*           | Scheduling algorithm (`fifo` or `edf`)                               |

### Example

```bash
./codexion 3 800 100 100 100 3 500 fifo
```

---

## Architecture

The simulation consists of three main components:

### Coders

Each coder is represented by a dedicated POSIX thread and continuously performs the following cycle:

```
Compile → Debug → Refactor → Repeat
```

A coder terminates when:

* It reaches the required number of compilations, or
* It experiences a burnout event.

---

### Dongles

Dongles are shared resources protected by synchronization primitives.

Their responsibilities include:

* Exclusive ownership management
* Cooldown tracking
* Fair access scheduling
* Thread wake-up signaling

---

### Monitor

A dedicated monitoring thread continuously supervises the simulation by:

* Tracking coder deadlines
* Detecting burnout conditions
* Detecting simulation completion
* Initiating a safe global shutdown

---

## Synchronization Mechanisms

The project relies on POSIX synchronization primitives to ensure thread safety.

### Mutexes

#### `mutex_time`

Protects coder-specific state variables:

* `last_compile_start`
* `compile_count`

#### `mutex_dead`

Protects the global simulation termination state.

#### `print_mutex`

Ensures atomic and ordered console output.

---

### Condition Variables

Each dongle contains its own condition variable:

```c
pthread_cond_t cond;
```

These condition variables allow threads to:

* Sleep efficiently while resources are unavailable
* Wait during cooldown periods
* Avoid CPU-intensive busy waiting

---

## Race Condition Prevention

Several strategies are employed to eliminate race conditions:

### Fine-Grained Locking

The monitor thread locks only the required state briefly:

```text
lock → read → unlock
```

This minimizes contention and preserves performance.

### Atomic Shutdown

When the simulation reaches a terminal state:

1. The global termination flag is updated atomically.
2. A broadcast signal wakes all blocked threads.
3. Threads release resources.
4. All threads terminate cleanly.

---

## Deadlock Prevention

To eliminate Coffman's Circular Wait condition, Codexion enforces a strict resource acquisition order.

Instead of requesting resources dynamically, coders acquire dongles according to a predetermined ordering strategy, guaranteeing deadlock-free execution.

---

## Starvation Prevention

To ensure fairness, Codexion supports scheduling strategies such as:

### FIFO (First-In First-Out)

Resources are allocated according to arrival order.

### EDF (Earliest Deadline First)

Priority is assigned to coders closest to their burnout deadline.

These strategies prevent indefinite resource monopolization.

---

## Dongle Cooldown System

After a dongle is released, it enters a temporary cooldown phase:

```text
release → cooldown → available
```

Threads waiting for cooling resources are suspended using condition variables rather than busy loops, reducing CPU usage and improving efficiency.

---

## Burnout Detection

The monitor thread operates independently and periodically evaluates:

```text
current_time - last_compile_start
```

If the elapsed duration exceeds `time_to_burnout`, the simulation immediately terminates.

The monitor executes at high frequency using fine-grained sleeping intervals to guarantee precise detection timing.

---

## Logging System

All console output is serialized using a dedicated mutex:

```c
pthread_mutex_t print_mutex;
```

This guarantees:

* Atomic log messages
* Correct timestamp ordering
* No output interleaving
* Readable concurrent execution traces

---

## Testing & Edge Cases

The project was stress-tested against numerous adversarial scenarios, including:

* Single coder simulations
* Immediate burnout conditions
* Large thread counts
* Heavy cooldown delays
* High contention environments
* Resource exhaustion scenarios
* Simultaneous termination events

---

## References

### Documentation

* POSIX Threads Programming Guide (Lawrence Livermore National Laboratory)
* GNU C Library Documentation
* POSIX Thread Specification

### Books

* *Modern Operating Systems* — Andrew S. Tanenbaum
* *Operating Systems: Three Easy Pieces*

---

## AI Usage

Artificial Intelligence tools were used exclusively as auxiliary development aids during the project's implementation.

Their usage included:

* Generating stress-test scenarios
* Identifying potential edge cases
* Reviewing concurrency architecture
* Assisting with code refactoring
* Improving modularity and maintainability
* Verifying compliance with the 42 Norm

All design decisions, synchronization mechanisms, algorithms, implementation details, and debugging procedures were ultimately developed, validated, and integrated by the author.

---

## Author

**hamezoua**
42 Network Student
