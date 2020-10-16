# profiler-program
A program that checks if a variable has changed in a specific place in a program.
To exectue, the program gets a few arguments:

  1+2: The specific segment in the code, via start and end addresses of the segment. Example: 400078 40007d
  
  3+: The program you want to debug, include its arguments. Example: time 500
  
  example to run the code:
  
  ./profiler-program 400078 40007d program arg1 arg2
  
Then, the program will get a collection of mappings in the format-
 
    <var_name> <register>
 
    <var_name> <register>
 
    ...
 
    run profile
  
  While- 
  
    var_name is the name of the variance we want to debug
  
    register is the register the variance is mapped to
  
    run profile is a command indicates the end of the input and to start the program
  
  example:
  
    i rcx
  
    sum rax
  
    run profile

Assumptions:  
We assume all the variables are saved in a register and not in addresses.
The input is correct.
Variable not longer than 256 characters.
Variables are not mapped to the following registers: r8-r15, rdi, rbp, rsp (in the future might get changed about r8-r15 registers).
We assume the variables are in their positive-signed range- MSB is always 0(might get changed in the future).
Addresses in hexadecimal.
The segment is eighter fully contain a loop or fully contained inside a loop.
If there is an OP error- immediately exit with exit error of 1.
The segment does not end with a jump/syscall/call/last command of the program.

