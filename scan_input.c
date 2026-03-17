#include "header.h"

// Global pointer to store the extracted command name
char *cmd;

// Array to store names of external commands read from file
char *external_cmd[154];

// Stores process ID returned by fork()
int pid;

// Stores status returned by wait/waitpid
int status;

// Head pointer for linked list (used elsewhere, e.g., command history)
Slist *head = NULL;

// Stores exit status of the last executed command
int last_exit_status = 0;

// Main loop that scans user input and executes commands
void scan_input(char *prompt, char *input_string)
{
    // Register signal handler for Ctrl+C (SIGINT)
    signal(SIGINT, signal_handler);

    // Register signal handler for Ctrl+Z (SIGTSTP)
    signal(SIGTSTP, signal_handler);

    // Load external commands from file into array
    extract_external_commands(external_cmd);

    // Infinite shell loop
    while (1)
    {
        pid = 0; // Reset PID before each command

        // Display shell prompt
        printf(GREEN "%s " RESET, prompt);

        // Read full input line until newline
        scanf("%[^\n]", input_string);
        getchar(); // Consume leftover newline character

        // Check if user is trying to modify the shell prompt (PS1=)
        if (strncmp(input_string, "PS1=", 4) == 0)
        {
            int flag = 1;

            // Start trimming trailing spaces
            int len = strlen(input_string) - 1;
            while (input_string[len] == ' ')
            {
                len--;
            }
            input_string[len + 1] = '\0';

            // Validate that prompt value contains no spaces
            for (int i = 4; i < len; i++)
            {
                if (input_string[i] == ' ')
                {
                    flag = 0;
                    printf("%s : Command not found\n", input_string);
                }
            }

            // If valid, update the shell prompt
            if (flag)
            {
                strcpy(prompt, &input_string[4]);
            }
        }
        else
        {
            // Extract the command name from input
            cmd = get_command(input_string);

            // Determine whether command is BUILTIN or EXTERNAL
            int type = check_command_type(cmd);

            // Execute built-in commands directly
            if (type == BUILTIN)
            {
                execute_internal_commands(input_string);
            }
            // Handle external commands using fork and exec
            else if (type == EXTERNAL)
            {
                pid = fork();

                if (pid > 0)
                {
                    // Parent process waits for child to finish or stop
                    waitpid(pid, &status, WUNTRACED);

                    // Store exit status if child exited normally
                    if (WIFEXITED(status))
                        last_exit_status = WEXITSTATUS(status);
                    // Store signal-based exit status if terminated by signal
                    else if (WIFSIGNALED(status))
                        last_exit_status = 128 + WTERMSIG(status);
                }
                else if (pid == 0)
                {
                    // Child process: restore default signal behavior
                    signal(SIGINT, SIG_DFL);
                    signal(SIGTSTP, SIG_DFL);

                    // Execute the external command
                    execute_external_commands(input_string);

                    // Exit child if exec fails
                    exit(0);
                }
            }
            else
            {
                printf("%s: command not found\n", input_string);
            }
        }
    }
}
