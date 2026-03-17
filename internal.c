#include "header.h"

// Stores status returned by wait / waitpid
extern int status;

// Stores exit status of the last executed command
extern int last_exit_status;

// Executes builtin shell commands
void execute_internal_commands(char *input_string)
{
    // Exit the shell
    if (strcmp(input_string, "exit") == 0)
    {
        exit(0);
    }

    // Print current working directory
    else if (strcmp(input_string, "pwd") == 0)
    {
        char buff[50];
        getcwd(buff, 50);
        printf("%s\n", buff);
    }

    // Change directory command
    else if (strncmp(input_string, "cd", 2) == 0)
    {
        char buff[50];

        // Change directory to the path after "cd "
        int ret = chdir(input_string + 3);
        // printf("%d", ret);

        // Print error if directory change fails
        if (ret == -1)
        {
            perror("chdir");
        }
        else
        {
            // Print new working directory after successful change
            getcwd(buff, 50);
            printf("%s\n", buff);
        }
    }

    // Print PID of the current shell process
    else if (strcmp(input_string, "echo $$") == 0)
    {
        printf("%d \n", getpid());
    }

    // Print exit status of the last executed command
    else if (strcmp(input_string, "echo $?") == 0)
    {
        printf("%d\n", last_exit_status);
    }

    // Print value of SHELL environment variable
    else if (strcmp(input_string, "echo &SHELL") == 0)
    {
        char *str;
        str = getenv("SHELL");
        printf("%s\n", str);
    }

    // Display background/stopped jobs
    else if (strcmp(input_string, "jobs") == 0)
    {
        print_list(head);
    }

    // Bring the most recent job to foreground
    else if (strcmp(input_string, "fg") == 0)
    {
        if (head != NULL)
        {
            // Resume stopped process
            kill(head->pid, SIGCONT);

            // Wait for it to finish or stop again
            waitpid(head->pid, &status, WUNTRACED);

            // Remove job from job list
            delete_first(&head);
        }
        else
        {
            printf("bash: fg: current: no such job\n");
        }
    }

    // Resume the most recent job in background
    else if (strcmp(input_string, "bg") == 0)
    {
        if (head != NULL)
        {
            // Enable SIGCHLD handling for background job
            signal(SIGCHLD, signal_handler);

            // Continue stopped process in background
            kill(head->pid, SIGCONT);

            // Remove job from job list
            delete_first(&head);
        }
        else
        {
            printf("bash: bg: current: no such job\n");
        }
    }
}