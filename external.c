// #include <stdio.h>
#include "header.h"

// Reads external command names from a file and stores them in an array
void extract_external_commands(char **external_commands)
{
    int fd;

    // Open the file containing external commands in read-only mode
    fd = open("ext_cmd.txt", O_RDONLY);

    char ch;              // Variable to read one character at a time
    char buff[50];        // Buffer to store one command line
    int i = 0;            // Index for buffer
    int j = 0;            // Index for external_commands array

    // Read the file character by character
    while (read(fd, &ch, 1) == 1)
    {
        buff[i++] = ch;   // Store character in buffer and increment index

        // If newline is encountered, one command is complete
        if (ch == '\n')
        {
            buff[--i] = '\0';   // Replace newline with string terminator
            i = 0;              // Reset buffer index for next command

            // Allocate memory for the command string
            int len = strlen(buff) + 1;
            external_commands[j] = malloc(len);

            // Copy command into the array
            strcpy(external_commands[j], buff);
            j++;                // Move to next command slot
        }
    }

    // Handle the last command if file does not end with newline
    buff[i] = '\0';

    int len = strlen(buff) + 1;
    external_commands[j] = malloc(len);
    strcpy(external_commands[j], buff);

    // Close the file descriptor
    close(fd);
}

// Executes an external command entered by the user
void execute_external_commands(char *input_string)
{
    int pipeflag = 0;              // Flag to detect presence of pipe '|'
    int len = strlen(input_string);
    int row = 1;                   // Counts number of arguments

    // Scan input string to detect pipes and count arguments
    for (int i = 0; i < len; i++)
    {
        if (input_string[i] == '|')
        {
            pipeflag = 1;          // Pipe detected
        }
        if (input_string[i] == ' ')
        {
            row++;                 // Increment argument count on space
        }
    }

    // Argument vector for execvp (last element must be NULL)
    char *argv[row + 1];

    int i = 0;

    // Create a modifiable copy of input_string for tokenization
    char *cmd = malloc(strlen(input_string) + 1);
    strcpy(cmd, input_string);

    // Tokenize the input string using space as delimiter
    char *token = strtok(cmd, " ");
    while (token != NULL)
    {
        argv[i++] = token;         // Store each argument
        token = strtok(NULL, " ");
    }

    argv[i] = NULL;                // execvp requires NULL-terminated argv

    // Execute command only if no pipe is present
    if (pipeflag == 0)
    {
        execvp(argv[0], argv);     // Replace process with external command
    }
    else
    {
        // pipe execution
        int *arr = malloc(sizeof(int) * 1); // array to store the starting index of each command
        arr[0] = 0;
        int count = 1; // count the no of pipes

        for (int i = 0; argv[i] != NULL; i++) // run loop upto null
        {
            if (strcmp(argv[i], "|") == 0) // if we found pipe
            {
                count++;                                 // increment count
                arr = realloc(arr, sizeof(int) * count); // allocate memory dynamically and add starting index of new command

                argv[i] = NULL;         // replace pipe with null
                arr[count - 1] = i + 1; // starting index of new command
            }
        }

        int pipe_fd[2];                 // declare array for pipe
        for (int i = 0; i < count; i++) // run loop upto count
        {
            if (i != count - 1) // i is not equal to count-1 we need to create pipe to run commands and pass output of one command to input of another command
            {
                pipe(pipe_fd); // creating pipe
            }
            int pid = fork(); // creating child process

            if (pid > 0) // parent process block
            {
                if (i != count - 1) // i not equal to count-1 then
                {
                    close(pipe_fd[1]);   // close pipe write end
                    dup2(pipe_fd[0], 0); // duplicate the read end to descripter no 0
                    close(pipe_fd[0]);   // close read end
                }
                waitpid(pid, NULL, 0); // wait for child to complete its execution
            }
            else if (pid == 0) // child process block
            {
                if (i != count - 1) // i is not equal to count-1 then
                {
                    close(pipe_fd[0]);   // close read end
                    dup2(pipe_fd[1], 1); // duplicate write end to descripter no 1
                    close(pipe_fd[1]);   // close the write end of pipe
                }
                execvp(argv[arr[i]], argv + arr[i]); // execute the commands
                perror("execvp");
                exit(1); // exit from child process
            }
        }
    }
}