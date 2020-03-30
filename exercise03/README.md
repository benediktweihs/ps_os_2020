# Exercise Sheet 3

In this exercise sheet you will schedule the execution of different processes
on paper. Several scheduling techniques will be analyzed.

| Process | Arrival Time | Service Time | Priority |
| ------- | ------------ | ------------ | -------- |
| A       | 0            | 7            | 2        |
| B       | 3            | 3            | 1        |
| C       | 4            | 2            | 3        |
| D       | 6            | 5            | 2        |
| E       | 8            | 2            | 3        |

The table above describes the arrival time, service time and priority of 5
different processes. Note that not all columns are required for all
algorithms below.

For each task in this exercise:

- create a GANTT chart describing how these processes are assigned to the CPU
  according to the given scheduling algorithms, and
- compute the average _turnaround time_ and _response time_ for each of these
  cases.

**Include the GANTT charts and the requested data into the file you submit via OLAT.**

Consider the following scheduling algorithms:

## Task 1

1. FCFS (First Come First Served)
2. SPN (Shortest Process Next - i.e., without preemption)
3. SRT (Shortest Remaining Time Next - i.e., with preemption)

## Task 2

4. Round Robin (quantum = 1)
5. Round Robin (quantum = 4)

Note that when a process is preempted, **it is always inserted to the back of
the queue**, after any processes that might have arrived in the meantime, or
even at the same time the preemption happens.

## Task 3

6. Highest Priority First with preemption
7. Highest Priority First without preemption

Note that a **higher number means higher priority**
(i.e., NOT [niceness](<https://en.wikipedia.org/wiki/Nice_(Unix)>)).
