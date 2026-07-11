````md
*This project has been created as part of the 42 curriculum by hamezoua.*

# Codexion

## Description

**Codexion** is a high-performance concurrent simulation project designed to explore advanced concepts in systems programming, including multithreading, synchronization, resource arbitration, and deterministic execution under strict timing constraints.

The project simulates a high-pressure software development environment where multiple **Coders** (implemented as POSIX threads) compete for a limited set of shared resources called **Dongles**. Each coder repeatedly cycles through several states:

- Compiling
- Debugging
- Refactoring

To survive, a coder must start a compilation within a predefined `time_to_burnout` interval. Failure to do so results in a burnout event, immediately terminating the entire simulation.

The project focuses on:

- Preventing race conditions
- Avoiding deadlocks
- Minimizing starvation
- Managing precise timing constraints
- Ensuring deterministic resource scheduling
- Performing a clean and safe shutdown of all threads

---

## Instructions

### Compilation

The project follows the 42 Norm and compiles with the following flags:

```bash
-Wall -Wextra -Werror -pthread
````

Build the project using:

```bash
make
```

### Execution

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

| Parameter                     | Description                                                          |
| ----------------------------- | -------------------------------------------------------------------- |
| `number_of_coders`            | Number of coder threads.                                             |
| `time_to_burnout`             | Maximum time (ms) before a coder burns out if no compilation starts. |
| `time_to_compile`             | Compilation duration (ms).                                           |
| `time_to_debug`               | Debugging duration (ms).                                             |
| `time_to_refactor`            | Refactoring duration (ms).                                           |
| `number_of_compiles_required` | Optional number of compilations required for each coder.             |
| `dongle_cooldown`             | Cooldown time (ms) after releasing a dongle.                         |
| `scheduling_policy`           | Scheduling algorithm (`fifo` or `edf`).                              |

### Example

```bash
./codexion 3 800 100 100 100 3 500 fifo
```

---

## Blocking cases handled

The implementation explicitly handles the following concurrency-related blocking cases:

* Deadlock prevention through deterministic resource acquisition ordering.
* Starvation prevention using FIFO and EDF scheduling strategies.
* Race condition prevention using fine-grained mutex protection.
* Efficient waiting for unavailable dongles using condition variables instead of busy waiting.
* Waiting during dongle cooldown periods without CPU spinning.
* Safe global shutdown by waking all blocked threads with `pthread_cond_broadcast()`.
* Correct handling of simultaneous burnout detection.
* Single-thread execution.
* High-contention scenarios with many competing threads.

---

## Thread synchronization mechanisms

The project uses POSIX thread synchronization primitives.

### Mutexes

* `mutex_time` protects each coder's timing information and compilation count.
* `mutex_dead` protects the global simulation termination state.
* `print_mutex` guarantees atomic and ordered console output.

### Condition Variables

Each dongle owns a condition variable:

```c
pthread_cond_t cond;
```

Condition variables are used to:

* Suspend threads while a dongle is unavailable.
* Wait during cooldown periods.
* Avoid busy waiting.
* Wake blocked threads when resources become available or when the simulation terminates.

---

## Resources

### Documentation

* POSIX Threads Programming Guide (Lawrence Livermore National Laboratory)
* POSIX Threads (IEEE POSIX Specification)
* GNU C Library Documentation
* Operating Systems: Three Easy Pieces
* Modern Operating Systems — Andrew S. Tanenbaum

### AI Usage

Artificial Intelligence tools were used only as development assistants.

They were used for:

* Reviewing the project architecture.
* Suggesting stress-test scenarios.
* Identifying possible edge cases.
* Improving code readability and modularity.
* Reviewing documentation and project organization.

All synchronization algorithms, concurrency mechanisms, implementation, debugging, testing, and final design decisions were implemented and validated by the author.

---

## Author

**hamezoua**
42 Network Student

```
```