# 42-minishell

## Overview
Minishell is a custom shell program written in C, designed to mimic some basic functionalities of [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)), the Bourne Again SHell. This project is part of the 42 School curriculum, aimed at deepening our understanding of system processes, file descriptors, and the intricacies of command-line interfaces. By creating our own shell, we delve into the core of Unix-based systems, learning to control processes, interpret user commands, and manage environmental variables.






## Team Development Steps for Minishell
### Step 1: Initial Planning and Setup
- **Repository Setup**: Collaboratively set up the GitHub repository, ensuring a clear directory structure and branch strategy.
- **Makefile Creation**: Makefile that includes rules for `all`, `clean`, `fclean`, `re`
- Set up libft libray

### Step 2: Research and Design Phase
#### Shell Operations: 
- [What Happens When You Type a Command in Your Terminal](https://www.youtube.com/watch?v=2P7fcVHxA9o&list=LL&index=6) 📹
- [Shell Code Explained](https://www.youtube.com/playlist?list=PLbtzT1TYeoMhF4hcpEiCsOeN13zqrzBJq) 📹

- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) 📹

- [Unix terminals and shells](https://www.youtube.com/playlist?list=PLFAC320731F539902) 📹

- [Terminal vs. Bash vs. Command line vs. Prompt](https://www.youtube.com/watch?v=hMSByvFHOro&ab_channel=LukeSmith) 📝

- [Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/) 📝


#### External Functions:
Reviewed the external functions allowed, dividing them among ourselves to research and explain their usage to the team.

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

### Step 3: Parsing and Input Management

#### Command Reading:
Implemented readline and integrated add_history

[GNU Readline](https://en.wikipedia.org/wiki/GNU_Readline)
```bash
brew install readline
```

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;
        if (*input)
            add_history(input);
        printf("Input: %s\n", input);
        free(input);
    }
    return 0;
}
```
[readline(3) - Linux manual page](https://man7.org/linux/man-pages/man3/readline.3.html)

