# Overview of Operating System

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
      - It does not because the OS is responsiblie for creating a PCB.
        It doesnt make sense for it to have one.
   - How is its state managed when it is not running? 
      - The state is managed by enabling the mode bit and ensuring that
        no other program, other than the OS it self, can modify the
        state when the OS is not running
* What is the difference between processes and threads? 
   - Processes have seperate CPU and Memory context while threads
     share the address space of a process with diffrent CPU contexts.
* What tasks are involved in switching the CPU from one
   process to another? 
   - Some sort of interrupt happens (i.e timer interupt, trap). The
     hardware copies the state of the program into memeory and
     simultaneously set the mode bit to privilaged. The address of part
     of the OS is placed into the PC and OS start executing.
   - Why is it called a context switch?
* What tasks are involved in switching the CPU from one 
  thread to another? 
   - Why are threads “lightweight”?
   
# Synchronization Primitives

## Mutual Exclusion
   1. No two processes simultaneously execute in critical section
   2. No assumption about speed and number of CPUs
   3. No process running outside its critical section may block another
      process.
   4. No process waits forever to enter its critical section

## Atomic Instructions
   * Test and Set Lock (TSL)
      1. Get the (old) value
      2. Set the lock to **True**
      3. Return the old value
         ```
         if returned value was FALSE
            lock is aquired
         if returned value was TRUE
            someone else has the lock
         ```
   * Compare and Swap/Exchange

## Locks
   * Ensure exclusive acess to shared data
   * Expresses intention to enter critical section
   * All threads must agree to aquire a lock before acessing the shared
     data

## Spinlocks
   * Also called polling, spinning or busy waiting. The thred consumes
     CPU cycles to evaluate when the lock become free
   ```c
      repeat
         while ( TSL(myLock) )
            no-op;
         ...
         critical section
         ...
         myLock = FALSE;
         ...
         remainder section
   ```
   * Problem on a single CPU. The busy waiting can prevent the holder
     of the lock from ever executing its critical section and releasing
     the lock

## Mutex
   > Implementation
   ```
   Threds waitingThreads[];
   Lock {
    oldIntStat = SetInterruptsTo (DISABLED)
       if (heldBy == Null) {
         heldBy = currentThread;
       } else {
         waitingThreads.add(currentThread);
         currentThread.Sleep();
       }
    oldIntStat = SetInterruptsTo(oldIntStat)
   }
   Unlock {
    oldIntStat = SetInterruptsTo (DISABLED)
       if (heldBy == currentThread) {
         thread = waitingThreads.Remove();
         if (thred != Null)
            readyList.add(thread);
       }
    oldIntStat = SetInterruptsTo(oldIntStat)
   }
   ```

## Semaphores
   > Implementation
   ```
   Up {
    oldIntStat = SetInterruptsTo (DISABLED)
       count = count + 1
       if (count <= 0) {
         t = waitingThreads.Remove ()
         t.status = READY
         readyList.AddToEnd (t)
       }
    oldIntStat = SetInterruptsTo(oldIntStat)
   }
   Down {
    oldIntStat = SetInterruptsTo (DISABLED)
       count = count - 1
       if (count < 0) {
         waitingThreads.AddToEnd (currentThread)
         currentThread.Sleep ()
       }
    oldIntStat = SetInterruptsTo(oldIntStat)
   }
   ```

   * `Wait(s) = Down(s) = P(s)`
   * `Signal(s) = Up(s) = V(s)`

## Monitors
   * Is an *abstract data type* that presents a set of
     programmer-defined operations that are provided mutual exclusion
     within the monitor.

## Condition Variables
   * Tailor-made synchronization scheme made by programmer
   * Only two methods `Down()` and `Up()` or `wait()` and `signal()`
   * `cv.wait()` mean the process invoked the operation is suspended
      until another process invoke `cv.signal()`
   > Implementation in Blitz
   ```c
      Condition {
         // Wait
         method Wait(Mutex m) {
          oldIntStat = SetInterruptsTo (DISABLED)
            m.Unlock()
             waitingThreads.AddToEnd (currentThread)
             currentThread.Sleep ()
            m.Lock()
          oldIntStat = SetInterruptsTo(oldIntStat)
         }
         // Sleep
         method Sleep() {
          oldIntStat = SetInterruptsTo (DISABLED)
          t = waitingThreads.Remove ()
          if t
            t.status = READY
            readyList.AddToEnd (t)
          endIf
          oldIntStat = SetInterruptsTo (oldIntStat)
         }
      }
   ```
   
# Recap
1. What is a race condition? 
   - When two or more threads manipulate shared data in such a way that
     it cause unexpected results. This hapen when two or more threads
     have inconsistent view of shared memory. i.e **whenever the result
     depends on the precise execution order of the thrads**
2. How can we protect against race conditions?
   - Prevent context switches by preventing interrpts
   - Make threds coordinate with each other to ensure **mutula
     exclusion** in accessing **critical sections** of code
3. Can locks be implemented simply by reading and 
   writing to a binary variable in memory?
   - No because simply reading and writing memory is not atomic. If the
     memory is shared resources, threds could end up having an
     inconsitent view.
4. How can a kernel make synchronization-related 
   system calls atomic on a uniprocessor? 
      - The kernel disables interupts gaurnteeing no context switches
        occur and after its critical section is done executing,
        inttrupts are eneabled.
      - Why wouldn’t this work on a multiprocessor?
         - Disabling interupt on one CPU does not mean another CPU
           disable interrupts. Another CPU can modify the memory. 
5. Why is it better to block rather than spin on a 
   uniprocessor?
      - By spining, the thread might not allow another process to
        execute its critical section and release the lock. By setting
        status to blocked, it gives a chance for the process holding
        the lock to run and release the lock.
6. Why is it sometimes better to spin rather than 
   block on a multiprocessor?
      - Context switching and process re-scheduling can be expensive.
        If threads are only likely to be blocked for short period,
        spinlocks are acceptable solutions.

# Concurrency Problems

## Produce Consumer (Bounded Buffer)
   > **Incorrect solution **
   ```c
   int count = 0;
   thread producer {
      while(true) {
         if (count == BUFFER_SIZE) {
            sleep();
         }
         item = produceItem();
         putItemInBuffer(item);
         count = count + 1;
         if (count == 1) {
            wakeup(consumer);
         }
      }
   }
   thread consumer {
      while(true) {
         if (count == 0) {
            sleep();
         }
         consumeItemFromBuffer();
         count = count - 1
         if (count == BUFFER_SIZE - 1) {
            wakeup(producer);
         }
      }
   }
   ```
   > **Only work for 1 producer and 1 consumer**
   ```c
   Semaphore fillCount = 0;
   Semaphore emptyCount = BUFFER_SIZE;
   thread producer() {
      while (true) {
         item = produceItem();
         down(emptyCount);
            putItemInBuffer(item);
         up(fillCount);
      }
   }
   thread consumer() {
      while (true) {
         down(fillCount);
            consumeItemFromBuffer();
         up(emptyCount);
      }
   }
   ``` 
   > **Correct Solution**
   ```c
   Mutex mutex;
   Semaphore fillCount = 0;
   Semaphore emptyCount = BUFFER_SIZE;
   thread producer() {
      while (true) {
         item = produceItem();
         down(emptyCount);
            mutex.Lock();
               putItemInBuffer(item);
            mutex.Unlock();
         up(fillCount);
      }
   }
   thread consumer() {
      while (true) {
         down(fillCount);
            mutex.Lock();
               consumeItemFromBuffer();
            mutex.Unlock();
         up(emptyCount);
      }
   }
   ``` 

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

# Deadlock Avoidance
https://www.cs.princeton.edu/courses/archive/fall09/cos318/lectures/SemaphoresMonitors.pdf
