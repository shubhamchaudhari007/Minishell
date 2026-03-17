#include "header.h"

// External array holding names of external commands
extern char *external_cmd[154];

// Stores the full input command entered by the user
extern char input_command[50];

// Current shell prompt string
extern char prompt[25];

// PID of the currently running child process
extern int pid;

// Stores child process exit status
extern int status;

// List of supported builtin shell commands
char *builtins[] = {
    "echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
    "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
    "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help",
    "jobs", "fg", "bg", NULL
};

// Extracts the command name (first word) from the input string
char *get_command(char *input_string)
{
    int len = strlen(input_string);
    char buff[50];     // Temporary buffer to store command
    int j = 0;

    int i = 0;

    // Skip leading spaces in input
    while (input_string[i] == ' ')
    {
        i++;
    }

    // Copy characters until space or end of string
    while (input_string[i] != '\0' && input_string[i] != ' ')
    {
        buff[j++] = input_string[i++];
    }

    buff[j] = '\0';    // Null-terminate extracted command

    // Allocate memory for command string
    char *cmd = malloc(j + 1);
    strcpy(cmd, buff);

    return cmd;
}

// Determines whether a command is BUILTIN, EXTERNAL, or invalid
int check_command_type(char *command)
{
    int i = 0;

    // Check against builtin commands
    while (builtins[i])
    {
        if (strcmp(command, builtins[i]) == 0)
        {
            return BUILTIN;
        }
        i++;
    }

    // Check against external commands list
    for (int j = 0; j < 152; j++)
    {
        if (strcmp(command, external_cmd[j]) == 0)
        {
            return EXTERNAL;
        }
    }

    // Command not found
    return NO_COMMAND;
}

// Inserts a job entry at the beginning of the linked list
void insert_at_first(Slist **head, int pid, char *input_string)
{
    // Allocate memory for new node
    Slist *new = malloc(sizeof(Slist));

    new->pid = pid;                    // Store process ID
    strcpy(new->cmd, input_string);    // Store command string
    new->next = NULL;

    // If list is empty, make new node the head
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        // Insert at beginning
        new->next = *head;
        *head = new;
    }
}

// Prints all jobs stored in the linked list
void print_list(Slist *head)
{
    if (head == NULL)
    {
        // No jobs to print
        // printf("No jobs\n");
    }
    else
    {
        int count = 1;
        while (head)
        {
            printf("[%d]  Stopped          %s\n", count,head->cmd);
            head = head->next;
            count++;
        }
    }
}

// Deletes the first node from the linked list
void delete_first(Slist **head)
{
    if (head == NULL)
    {
        printf("Error : no process\n");
    }
    else
    {
        Slist *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Custom signal handler for shell
void signal_handler(int sig_num)
{
    // Handle Ctrl+C (SIGINT)
    if (sig_num == SIGINT)
    {
        // If no child process is running
        if (pid == 0)
        {
            printf(GREEN"\n%s "RESET, prompt);
            fflush(stdout);
        }
    }

    // Handle Ctrl+Z (SIGTSTP)
    if (sig_num == SIGTSTP)
    {
        // If shell is idle
        if (pid == 0)
        {
            printf(GREEN"\n%s "RESET, prompt);
            fflush(stdout);
        }
        else
        {
            // Background the stopped process
            printf("\n");
            insert_at_first(&head, pid, input_command);
        }
    }

    // Handle child termination signal
    if (sig_num == SIGCHLD)
    {
        // Reap terminated child without blocking
        waitpid(-1, &status, WNOHANG);
    }
}
