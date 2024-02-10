# 42-minishell

## Overview
Minishell is a custom shell program written in C, designed to mimic some basic functionalities of (bash)[https://en.wikipedia.org/wiki/Bash_(Unix_shell)], the Bourne Again SHell. This project is part of the 42 School curriculum, aimed at deepening our understanding of system processes, file descriptors, and the intricacies of command-line interfaces. By creating our own shell, we delve into the core of Unix-based systems, learning to control processes, interpret user commands, and manage environmental variables.


## Team Development Steps for Minishell
### Step 1: Project Setup
- Initialized the project repository and set up the basic directory structure.
- Created a Makefile with rules for `all`, `clean`, `fclean`, `re`
- Set up libft libray

https://www.youtube.com/watch?v=hMSByvFHOro&ab_channel=LukeSmith


## External Functions

| Function                                       | Description                                                         |
| ---------------------------------------------- | ------------------------------------------------------------------- |
| `readline`                                     | Reads a line from the standard input and returns it.                |
| `rl_clear_history`                             | Clears the readline history list.                                   |
| `rl_on_new_line`                               | Prepares readline for reading input on a new line.                  |
| `rl_replace_line`                              | Replaces the content of the readline current line buffer.           |
| `rl_redisplay`                                 | Updates the display to reflect changes to the input line.           |
| `add_history`                                  | Adds the most recent input to the readline history list.            |
| `printf`                                       | Outputs formatted data to stdout.                                   |
| `malloc`                                       | Allocates specified bytes of heap memory.                           |
| `free`                                         | Deallocates previously allocated memory.                            |
| `write`                                        | Writes data to a file descriptor.                                   |
| `access`                                       | Checks calling process's permissions for a file or directory.       |
| `open`                                         | Opens a file or device, returning a file descriptor.                |
| `read`                                         | Reads data from a file descriptor into a buffer.                    |
| `close`                                        | Closes a previously opened file descriptor.                         |
| `fork`                                         | Creates a new process by duplicating the calling process.           |
| `waitwaitpid`                                 | Waits for a child process to change state.                          |
| `signal` <br> `sigaction`                             | Handles or ignores signals sent to the process.                     |
| `sigemptyset` <br> `sigaddset`                        | Initializes and adds signals to a signal set.                       |
| `kill`                                         | Sends a signal to a process or a group of processes.                |
| `exit`                                         | Terminates the calling process.                                     |
| `getcwd`                                       | Gets the current working directory.                                 |
| `chdir`                                        | Changes the current working directory.                              |
| `stat` <br> `lstat` <br> `fstat`                             | Returns information about a file or a file descriptor.              |
| `unlink`                                       | Removes a link to a file.                                           |
| `execve`                                       | Replaces the current process image with a new process image.        |
| `dup` <br> `dup2`                                     | Duplicates a file descriptor.                                       |
| `pipe`                                         | Creates a pipe for inter-process communication.                     |
| `opendir` <br> `readdir` <br> `closedir`                     | Manages directory streams.                                          |
| `strerror` <br> `perror`                              | Returns a pointer to the textual representation of an error code.   |
| `isatty`                                       | Tests whether a file descriptor refers to a terminal.               |
| `ttyname` <br> `ttyslot`                              | Returns the name of the terminal associated with a file descriptor. |
| `ioctl`                                        | Controls device-specific input/output operations.                   |
| `getenv`                                       | Returns the value of an environment variable.                       |
| `tcsetattr` <br> `tcgetattr`                          | Sets and gets terminal attributes.                                  |
| `tgetent` <br> `tgetflag` <br> `tgetnum` <br> `tgetstr` <br> `tgoto` <br> `tputs` | Terminal handling functions from the termcap library.               |
