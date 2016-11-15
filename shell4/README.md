# Wait and race conditions

* waitdemo: wait for a process to die

# Waiting for multiple events

New problem: Let's wait for the process to die, OR 0.75 sec, whichever
comes first. This relates to the functionality of the `timeout`
command.

* waitlimit-poll

This polling solution works, but uses a lot of CPU.

* waitlimit-block

This blocking solution works without wasting CPU, relying on the fact
that signals—such as `SIGCHLD`, which is delivered to a parent when a
child exits—interrupt long-running system calls.

But does it really work? Remove the usleep() in the child and replace
fork() with nfork(), then run it multiple times. You should eventually
see a problem!

* waitlimit-block2

This blocking solution appears to solve the problem by using signals
in a different way. This time, `SIGALRM` interrupts `waitpid`.

This seems more reliable in practice. But does *it* really work in
*all* situations?

* waitlimit-block3–waitlimit-block5

These blocking solutions really do work.
