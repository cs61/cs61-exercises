Here is the code we worked through in class for OS02. Each successive
modification is checked in to a git branch. You should be able to
examine a specific branch with `git checkout origin/BRANCHNAME`, and
to see differences with `git diff master origin/v02` and similar
commands. Remember to return to the master branch with
`git checkout master` when you're done.

* master: initial OS02.
* v01: Evil: alloc attacks the kernel with a bad argument.
* v02: Good: kernel checks its arguments more carefully.
* v03: Evil: alloc attacks the kernel with another bad argument.
* v04: Good: kernel checks its arguments even more carefully.
* v05: Kernel adds automatic stack page allocation (for recurse).
* v06: Evil: recurse tries to kill the kernel.
* v07: Good: kernel checks stack page allocation.
* v08: A version of fork.
* v09: Good: Kernel starts checking argument to panic system call.
* v10: Good: Kernel completes checking argument to panic system call.
