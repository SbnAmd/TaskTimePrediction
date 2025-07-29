# Project Overview

This project extracts runtime characteristics of soft real-time tasks and uses them to predict task execution times. The aim is to improve the accuracy of execution time estimation by leveraging hardware performance counters.

## Requirements

- **PREEMPT_RT Kernel Patch:**  
  The kernel must be patched with the PREEMPT_RT version to support real-time scheduling policies such as:
  - `SCHED_FIFO`
  - `SCHED_RR`
  - `EDF` (Earliest Deadline First)

  These policies are essential for deterministic task scheduling in real-time systems.

## Performance Events

Performance events are hardware-level metrics collected by modern processors. These counters provide insights into program execution, including:

- **Cache Misses:** Times data was not found in the CPU cache, causing slower memory access.
- **Branch Mispredictions:** Incorrect CPU branch predictions, leading to pipeline stalls.
- **Instruction Count:** Total instructions executed by the CPU.
- **CPU Cycles:** Number of clock cycles consumed during execution.
- **Memory Accesses:** Number of memory accesses during execution.
- **Context Switches:** Number of times the CPU switched between tasks.

Analyzing these events helps understand task runtime behavior and improves the accuracy of execution time prediction models. Bottlenecks can be identified and addressed using these metrics.

## Current Implementation

- **Performance Events:**  
  Six performance events are currently used to predict and evaluate execution time precision. Events are enabled, read, and disabled in groups for efficiency.
- **Benchmark Integration:**  
  The MiBench benchmark suite is integrated (some benchmarks remain due to legacy issues).
- **🔴 Because preemption is not working according to threads priority with SCHED_FIFO, this project is not going to work. Works must be done to fix this.** 

## Future Work

- Optimize performance event selection for improved prediction accuracy.
- Refine the task time prediction model.

---

**Note:**  
🔴 Development is suspended. Contributions are welcome!
