# Parallel Solutions Repository

This repository contains three implementations of parallel algorithms in C: a **Parallel Producer-Consumer Problem**, a **Parallel Quicksort Algorithm**, and a **Dining Philosophers Problem**. Each project demonstrates effective use of threading and synchronization techniques.

## Producer-Consumer Problem

### Description
The Producer-Consumer problem illustrates the challenge of coordinating the production and consumption of items in a shared buffer. This implementation uses threads to allow producers to create items and consumers to consume them concurrently while ensuring safe access to the shared buffer.

### Features
- Utilizes **POSIX threads** (`pthread` library) for concurrent execution.
- Implements **mutexes** and **condition variables** to manage synchronization between producers and consumers.

### Code Structure
- `producer_consumer.c`: Main implementation of the producer-consumer problem.

---

## Quicksort Algorithm

### Description
The Quicksort algorithm is an efficient sorting algorithm that employs a divide-and-conquer strategy. This implementation replaces the traditional recursive approach with an iterative approach using a stack to manage unsorted sub-arrays. It also uses OpenMP to parallelize the sorting process, allowing multiple threads to work on different segments of the array simultaneously.

### Features
- Implements the Quicksort algorithm using a partitioning method.
- Utilizes **OpenMP** for parallel execution to improve sorting efficiency.
- Provides verification of the sorted array.

### Code Structure
- `quick_sort.c`: Main implementation of the parallelized Quicksort algorithm.

---

## Dining Philosophers Problem

### Description
The Dining Philosophers problem is a classic synchronization problem that illustrates the challenges of resource sharing and process synchronization. In this implementation, five philosophers alternately think and eat, but they need chopsticks to eat. The challenge is to avoid deadlock while ensuring that each philosopher gets to eat.

### Features
- Utilizes **POSIX threads** for concurrent execution.
- Implements **semaphores** for managing access to chopsticks and ensuring that no deadlock occurs.
- Demonstrates proper handling of philosopher states (thinking, hungry, eating).

### Code Structure
- `dining_philosophers.c`: Main implementation of the dining philosophers problem.

---

## Installation

To compile and run the programs, ensure you have a C compiler that supports OpenMP and pthreads installed on your machine (e.g., GCC).
