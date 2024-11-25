# Philosophers

Philosophers is a project that simulates a classic concurrency problem. It demonstrates how processes and threads can manage shared resources efficiently using synchronization tools like mutexes and semaphores.

<img src="./philos_tables.png" alt="philosophers 42 table" width="500px" height="500px">

---

## **Overview**

The program represents philosophers sitting at a round table with a shared bowl of spaghetti. Each philosopher alternates between eating, thinking, and sleeping while avoiding starvation. The challenge is to manage resource sharing (forks) without causing deadlock or race conditions.

---

## **Features**

- **Thread-based Implementation** (mandatory): Uses threads and mutexes to simulate the philosophers.
- **Dynamic Simulation**: Handles a configurable number of philosophers and timings.
- **Error Handling**: Validates arguments and prevents invalid input.

---

## **How to Use**

### **Compiling the Program**

Use the provided `Makefile` to compile the project:

- **Mandatory**:
  ```bash
  make
  ```


### **Running the Program**
Run push_swap with a list of integers as arguments:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```

**Arguments:**
- number_of_philosophers: Number of philosophers and forks.
- time_to_die (ms): Time a philosopher can go without eating before starving.
- time_to_eat (ms): Duration of eating.
- time_to_sleep (ms): Duration of sleeping.
- (Optional) number_of_times_each_philosopher_must_eat: Stops simulation after all philosophers have eaten this many times.

**Example**

```bash
./philo 5 800 200 200
```
This starts a simulation with 5 philosophers who have 800ms to eat before starving, and 200ms for eating and sleeping cycles.

---

### **Output**
Each philosopher's state changes are logged with timestamps, including:
- Taking a fork.
- Eating.
- Sleeping.
- Thinking.
- Dying (if applicable).

```bash
200 1 has taken a fork
201 1 is eating
401 1 is sleeping
1201 1 is thinking
...
```

---

## **Error Handling**
The program checks for:
- Invalid argument formats.
- Non-numeric inputs or negative values.
- Integers exceeding the valid range (INT_MIN to INT_MAX).
- Logical errors.

---

## **File Structure**
- philo/: Mandatory part implementation.
- studying/: All the concepts that I studied separetly before creating the program.

