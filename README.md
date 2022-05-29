# goto-c

This is a small demonstration about the effectiveness of using `goto` instead of function calls.
When performance is crucial, `goto` can be a means of optimization.
It also reminds us that calling functions is not free.
It needs to save the stack pointer, create a new stack frame, initialize local variables if any.
Similarly, the return of a function needs to store the return value, remove the stack frame, and
restore the stack pointer. Although all this is hidden from us, and happens in the background,
it's still happening, while `goto` is just one single jump operation in machine code - hence the
performance gain.

The app calculates the 1000th Fibonacci number a given number of times both using function calls
and `goto`, measures the time consumption, and compares the result.

Although the overall result may depend on other factors as well, usually code with `goto`
performs considerably better. This can mean up to two times the performance of the code written
using function calls, if our compilers do a great job optimizing our code, or up to 13 times
faster if not (see [Visual Basic version](https://github.com/auxiliaire/GotoApp)).

## Verdict

**Never prematurely optimize your code!**

Although `goto` performs better, this is simply not enough reason to start using it for it may
complicate the code. Instead try to write clean code, and optimize only when you can put your
finger on a certain point that proved to be a bottleneck in your application.

## Code

This program is written in vanilla C and can be compiled with GCC or Clang by changing one line
in the Makefile. Another version is available written in Microsoft Visual Basic
[here](https://github.com/auxiliaire/GotoApp).

## Screenshots

![Output of the app compiled with GCC](/screenshots/goto-gcc.png "GoTo performance comparison (GCC)")

![Output of the app compiled with Clang](/screenshots/goto-clang.png "GoTo performance comparison (Clang)")
