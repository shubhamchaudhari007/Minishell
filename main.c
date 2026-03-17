#include "header.h"
#include <stdio.h>
#include <stdlib.h>

/*
Name : Shubham Sanjay Chaudhari
ID : 25021c_306

project : MINISHELL
This project involves the design and implementation of a custom Linux Mini Shell using the C programming language and POSIX system calls. The shell emulates essential behaviors of a Unix/Linux command-line interpreter and provides hands-on exposure to process management, signal handling, job control, and command execution at the operating-system level.

The shell continuously accepts user input, parses commands, and determines whether the command is a built-in command or an external system command. Built-in commands such as cd, pwd, exit, echo, jobs, fg, and bg are executed internally without creating new processes, while external commands are executed using fork() and execvp().

A key feature of the project is job control. The shell supports background and foreground process management using signals like SIGINT, SIGTSTP, and SIGCHLD. When a process is stopped using Ctrl+Z, it is tracked in a linked list, allowing users to resume it later using fg or bg. Proper handling of child process termination ensures there are no zombie processes.

The shell also supports:

Custom prompt configuration using PS1=

Exit status tracking (echo $?)

Process ID retrieval (echo $$)

Environment variable access (e.g., SHELL)

Graceful signal handling for interactive use

External commands are validated against a predefined command list loaded from a file, improving command classification efficiency. Input parsing is carefully implemented to handle spaces and command arguments reliably.

Overall, this project demonstrates a strong understanding of Linux internals, system-level programming, and shell architecture, making it a solid foundation for learning advanced topics such as pipelines, redirection, and full POSIX-compliant shell development.

*/
char prompt[25] = "MINISHELL$:";
char input_command[50];

int main()
{
    system("clear"); // clear the terminal

    scan_input(prompt, input_command); // take input command from user
}