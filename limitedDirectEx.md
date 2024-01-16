Slide Image for Process Switch due to a timer interrupt. Jan 15, 2024

1. **Run main()**
   - The CPU begins by running the main function of a process (let's call it Process A).

2. **Timer Interrupt**
   - The CPU receives a timer interrupt, indicating that Process A's allocated time slice for CPU execution has finished. The hardware saves the CPU state (registers) of Process A to the kernel stack for Process A.

3. **Switch to kernel mode**
   - The CPU switches from user mode to kernel mode, which is a protected mode where the operating system's kernel can execute sensitive tasks.

4. **Jump to trap handler**
   - The CPU control is transferred to a trap handler, which is part of the operating system's interrupt or exception handling code.

5. **Handle trap, call switch routine**
   - The trap handler calls a context switch routine, which will facilitate switching from Process A to Process B.
   - The current CPU state (registers) of Process A is saved

to the process's PCB (proc_t(A) in the pseudo-code). The PCB of a process stores all the information about the process state, so it can be resumed later.

6. **Save CPUReg(A) to proc_t(A)**
   - The CPU registers for Process A are saved into its PCB, ensuring that when Process A is resumed, it can continue from where it was interrupted.

7. **Restore CPUReg(B) from proc_t(B)**
   - The CPU registers for Process B are loaded from its PCB into the CPU. This prepares the CPU with Process B's last known state.

8. **Switch to kernel_stack(B)**
   - The stack pointer is switched to use Process B's kernel stack. Each process has its own kernel stack in the system.

9. **Return from trap**
   - The system finishes the trap handler and prepares to return control to user space, but for Process B this time.

10. **Restore CPUReg(B) from kernel_stack(B)**
    - The CPU registers for Process B are restored from the kernel stack as part of the final steps to move back into user mode.

11. **Switch to user mode**
    - The CPU changes its mode from kernel (privileged) mode

to user mode. In user mode, the process cannot perform privileged operations directly; it must communicate with the kernel to do so.

12. **Jump to B’s PC**
    - The CPU now jumps to the program counter (PC) of Process B. The program counter holds the memory address of the next instruction to be executed by the CPU.

13. **Continue running**
    - Process B continues its execution from where it left off before it was previously switched out by the operating system.

The pseudo-code on the right side of the image provides a high-level representation of the context switching process:

```python
def switch(old, new):
    proc_t(old) = get_cpu_registers() # Save old process's CPU state
    set_cpu_registers(new->proc_t)    # Load new process's CPU state
    set_kernel_stack(new->kstack)     # Switch to the new process's kernel stack
    ReturnFromTrap()                   # Return control to the new process
```

The pseudo-code corresponds to the steps listed, showing the functions that might be involved in the context switch operation. The 'switch' function takes the old and new process as arguments, saves the CPU state of the old process, and restores the state of the new process before returning from the trap handler to resume execution of the new process

Saving the CPU registers of Process A to both the kernel stack and the PCB might seem redundant at first, but each serves a different purpose during the context switch process:

1. **Saving to the Kernel Stack:**
   - When a timer interrupt occurs, or any interrupt for that matter, the CPU automatically saves the current state (including some of the registers) to the kernel stack as part of the interrupt handling routine. This is hardware-driven and ensures that the interrupt service routine has a consistent environment to operate in and can safely return to the interrupted code.

2. **Saving to the PCB:**
   - The PCB is the data structure used by the operating system to store all the information about a process. It is used to hold the context of the process when it is not running. The PCB needs to contain a full snapshot of the process's state, including all the CPU registers, so that the process can be resumed later at the exact point it was interrupted. This is a software-driven step and is part of the context switch routine managed by the operating system.

Here's why both steps are necessary:

- The save to the kernel stack is a temporary measure that happens automatically by the CPU's interrupt mechanism. It's part of the low-level handling of an interrupt and is meant to preserve the state just for the duration of the interrupt handling.

- Saving to the PCB is done explicitly by the operating system's context switch code and is necessary to manage the process over a longer term. When the operating system decides to switch back to Process A, it will look into Process A's PCB to restore its state.

In some systems or under certain conditions, these steps might be optimized to avoid duplication, but conceptually, they represent different stages of interrupt handling and process management.
