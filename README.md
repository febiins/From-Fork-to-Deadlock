# Operating System Programming in C

Learning Operating System concepts by implementing them in C.

Goal:
- Understand OS concepts deeply
- Prepare for technical interviews
- Build practical knowledge through programming
- Document learning journey publicly

---

## Roadmap

### Week 1: Memory & Pointers
Topics:
- Stack vs Heap
- malloc(), calloc(), free()
- Memory leaks
- Dangling pointers

Programs:
- stack_vs_heap.c
- malloc_demo.c
- memory_leak.c

---

### Week 2: Processes
Topics:
- Process creation
- fork()
- getpid()
- getppid()
- Zombie process
- Orphan process

Programs:
- fork_basic.c
- zombie_process.c
- orphan_process.c

---

### Week 3: Threads
Topics:
- pthread_create()
- pthread_join()
- Process vs Thread
- Shared memory

Programs:
- thread_basic.c
- multiple_threads.c

---

### Week 4: Synchronization
Topics:
- Race condition
- Mutex
- Semaphore
- Critical section

Programs:
- race_condition.c
- mutex_demo.c
- semaphore_demo.c

---

### Week 5: Deadlocks
Topics:
- Deadlock conditions
- Deadlock prevention
- Banker's Algorithm

Programs:
- deadlock.c
- bankers_algorithm.c

---

### Week 6: Classical Synchronization Problems
Topics:
- Producer Consumer
- Reader Writer
- Dining Philosophers
- Sleeping Barber

Programs:
- producer_consumer.c
- reader_writer.c
- dining_philosopher.c

---

### Week 7: CPU Scheduling
Topics:
- FCFS
- SJF
- Round Robin
- Priority Scheduling

Programs:
- fcfs.c
- round_robin.c

---

### Week 8: Memory & Disk Scheduling
Topics:
- Paging
- FIFO
- LRU
- Disk Scheduling
- SCAN / C-SCAN

Programs:
- lru.c
- fifo.c
- scan.c

---

## Interview Topics Covered

- Process vs Thread
- Mutex vs Semaphore
- Stack vs Heap
- Deadlocks
- Scheduling Algorithms
- Memory Management

---

Learning one concept at a time and implementing every topic in C.

Note:- Since system calls work only on Linux, Windows users should use WSL (Windows Subsystem for Linux). 
