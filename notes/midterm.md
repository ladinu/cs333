# Overview of Operating Systems

## What is an Operating System?
   * Just a program
   * Controls execution of application programs
   * Implements a interface between the user and hardware

## Operating System Roles
   * Contols access to shared resources (CPU, Memory, Disk, Network, ...)
   * Provide a common API to applications which simplify application
     writing
   * Take care of the hardware details and provide a higher-level
     abstraction to applications and users
   * Resource Management
      - Make efficient use of limited resources 
      - time/space sharing resources
   * Protect applications from each other
   * Also protect the OS itself

## Hardware and the OS
   * The CPU blindly fetch, decode and execute instructions
   * **Program Counter** (PC): holds the memory address of the *next*
     instruction
   * **Instruction Register** (IR): holds the instruction *currently*
     being executed
   * **General Registers** (Reg 1..n): holds variables and temp result
   * **Stack Pointer** (SP): holds memory address of a stack with a
     frame for each active procedure parameter's & local vars'. Always
     points to the top of the stack
   * **Processor Status Word** (PSW): contain contol bits including the
     **mode bit** which determine if privileged instructions can be
     executed

## OS Regain Control and Interrupts
   * OS needs **interrupts** from a timer device
   * OS must register a future timer interrupt before handing
     application control of the CPU
   * When timer interrupt goes off, the harware start running the OS at
     a pre-specified location  called an *interrupt handler*
   * Interrupt handler is part of the OS program
   * The address of the interrupt handler's first instruction is placed
     in the PC by the hardware'

## Traps
   * Traps are deliberate while interrupts are not
   * Disabling interrpts is a privilaged instruction and cannot be
     executed by applications (generally cause a trap)
   * Application invoke OS by trap instructions which cause a kind of
     interrupt. It 
      - changes PC to point to predetermined OS entry point instruction
      - simultaneously sets the mode bit
   * Applications calls a library procedure that includes trap
     instructions
   * Traps are synchronous where interrupts are asynchronous (i.e traps
     are coaused by programs rather than a device external to the CPU)


# Recap
   * Why do we need a timer device?
      - The CPU blindly fetch, decode and execute instructions. We need
        an external device such as a *timer device* to generate
        interrupts once in a while so the OS get a chance to run. It
        also keeps track of time.
   * Why do we need an interrupt mechanism? 
      - Interrupt mechanisms are needed so that the OS gets a chance to
        run. Without this, user processes can hog the CPU by not
        letting anything else run. Interrupts are also used as signals
        by other devices on the computer to signal the CPU
   * Why do we need privileged instructions?
      - Privilaged instructions can only be executed when the mode bit
        is set. If the OS unset the mode bit before a application
        program is run, the application cannot execute privilaged
        instructions such as disabling interrupts. Privilaged
        instructions ensure that only the OS get to run instructions
        which ensure fair usage of computer resources.
   * Why are system calls different to procedure calls?
      - System calls cause a context switch to the OS by using a trap
        instruction where as a procedure call do not. System calls are
        abstractions provided by the OS which take care of low level
        details.
   * How are system calls different to interrupts?
      - System calls are deliberate and interrupts are not. System
        calls usually execute a trap instruction. System calls are
        usually called by user programs. Sys calls invoke the OS via
        trap instruction
   * Why is memory protection necessary?
      - Memeory protection is needed to protect applications from one
        another and have the OS remain in control. Without memory
        protection application can modify the OS and take control.
   * How can the OS switch among applications?
      - The scheduler determine which application to be run next. The
        operating system capture the application memory and processor
        state. These are saved in memory. Restarting the application
        requires reloading the saved state into memory and CPU.

# Memory

## Memory Protection
   * Virtual vs Physical adresses
      - Adress range for each app starts at 0
      - App use virtual adresses, but hardware translate those to
        physical adresses
   * Base Register
      - CPU interpret adress inderectly vis base register
      - Add base value to adress to get real adress of memory
   * Paged Virtual Memory
      - Supports non-contiguous allocation of memory
      - Require hardware support for adress translation
      - Allows process to grow and shrink dynamically  

# Devices
   * Device drivers are port of the OS
   * Progrmas call the OS which calls device driver
   * Device drivers interact with divice controllers
   * The controllers appear as memory locations
   * Device controller are hardware which communicate with device
     drivers (OS) via interrupts


# Processes vs Threads

## Process
   * A program in execution
   * A snapshot of a program in execution. (state of memory, CPU state,
    S state such as open files, ...)
   * Each process runs in its own *virtual memory address space* which
     consist of:
      - Stack space (function and system calls)
      - Data space (static and dynamic vars)
      - Text (the program code, usually read only)
   * Process can have any of the following states at a given time:
      1. Running
      2. Ready
      3. Blocked
   * `fork()` system call create a copy of a process and returns in both
     processes (parent and child) with diffrent return values.
      ```c
         int pid = fork();
         if (pid == 0) {
            // Child
            print("Child");
         } else {
            // Parent
            print("Parent");
         }
      ```
   * Processes communicate via IPC system calls because they have
     seperate CPU and memory context

   * Traditional process can ve viewd as a memory adress space with a
     single thread.
   * Each process the OS has a Process Control Block (PCB) with the
     following info
      - **Process State** - Running, Waiting, New, Ready, Terminated
      - **Process ID** and parent process ID
      - **CPU state** used to restore process
      - **CPU Scheduling info** - priority info
      - **Memory-Management Info** - page table or segment tables

## Thread
   * Threads share a process address space with zero or more threads
   * Threads have their own CPU context
      - PC, SP, register state
      - Stack
   * No need to use system calls to communicate with other threads as
     they share memory space (i.e heap)
   * Pros:
      - Overlap I/O with computation
      - Cheaper context switches
      - Better usage of multiprocessors
   * Cons:
      - Potential thread interaction
      - Complexity of debugging
      - Complexity of multi-threaded programming

# Recap
* What is the difference between a program and a process?
   - A program is a list of instructions on how to perform an activity
     with static data value while a process is a program in execution. 

* Is the Operating System a program?
   - Yes. The source code of the OS is a set of instructions describing
     how to do an activity
* Is the Operating System a process? 
   - Does it have a process control block? 
   - How is its state managed when it is not running? 
* What is the difference between processes and threads? 
   - Processes have seperate CPU and Memory context while threads
     share the address space of a process with diffrent CPU contexts.
* What tasks are involved in switching the CPU from one
   process to another? 
   - Why is it called a context switch? 
* What tasks are involved in switching the CPU from one 
  thread to another? 
   - Why are threads “lightweight”?
   
# Synchronization Primitives

## Atomic Instructions

## Locks

## Spinlocks

## Mutex Sempahores

## Counting Semaphores

# Concurrency Problems

## Produce Consumer (Bounded Buffer)

## Dining Pnilosophers

## Readers and Writers

## Sleeping Barber

## Critical Section

   * When a process `p1` is executing in a critical section, no other
     process is allowed to execute in that section
   * Process need permission to enter a critical section. In the code
     there are 2 sections `entry` and `exit` section
      - ```javascript
         do {
            entry section
               critical section
            exit section
               remainder section
         } while (True)
        ```
   * A solution to critical-section problem must satisfy the following
     3 conditions
      1. [**Mutual exclusion**](#mutual-exclusion)
      2. [**Progress**](#progress)
      3. [**Bounded waiting**](#bounded-waiting)

## Mutual Exclusion 

   * If process `P1` is executing in its critical section, then no other
    process can be executing in their critical sections

## Progress
   * 
