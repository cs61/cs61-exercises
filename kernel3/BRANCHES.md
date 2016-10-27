Here is the code we worked through in class as we developed OS01 into
an operating system with process isolation. Each successive
modification is checked in to a git branch. You should be able to
examine a specific branch with `git checkout origin/BRANCHNAME`, and
to see differences with `git diff master origin/v02` and similar
commands. Remember to return to the master branch with
`git checkout master` when you're done.

* master: initial, un-isolated OS01.
* v01: Nasty: hello enters an infinite loop.
* v02: Nice: kernel uses a timer interrupt.
* v03: Nasty: hello disables interrupts.
* v04: Nice: kernel prevents hello from disabling interrupts.
* v05: Nice: kernel reacts to fault by blocking process.
* v06: Nasty: hello replaces kernel code with an infinite loop.
* v07: Nice: kernel prevents processes from modifying kernel memory.
* v08: Nice: kernel responds to page fault by blocking faulting process.
* v09: Nice: skip over hello's evil instruction.
* v10: Nasty: hello erases welcome's code.
* v11: Nice: give hello an isolated page table.
* v12: Nasty: confused deputy: hello convinces the kernel to give it
  permission to disable interrupts.
* v13: Nice: kernel checks for confused deputy (partially).
