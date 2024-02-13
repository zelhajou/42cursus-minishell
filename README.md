
# Overview
Our Minishell project represents a collaborative effort to build a custom shell program in C, inspired by the functionalities of [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)), the Bourne Again SHell. As part of the 42 School curriculum, this project served as a unique opportunity for us to deepen our collective understanding of system processes, file descriptors, and the complexities of command-line interfaces. Through the development of our own shell, we engaged in a comprehensive exploration of Unix-based systems, gaining hands-on experience in process control, command interpretation, and environmental variable management.

# Project Challenges

- **Parsing User Input**: Accurately parsing user input, including handling spaces, quotes, and special characters, while distinguishing between command arguments and options.
- **Executing Commands**: Implementing logic to search for and execute the right executable based on the PATH environment variable or a specified path, and managing execution of built-in commands versus external commands.
- **Signal Handling**: Correctly handling Unix signals such as SIGINT (`ctrl-C`), SIGQUIT (`ctrl-\`), and EOF (`ctrl-D`), and ensuring the shell behaves similarly to bash in response to these signals.
- **Input/Output Redirection and Pipes**: Implementing input and output redirection (`<`, `>`, `>>`, `<<`) and pipes (`|`) to allow for command chaining and data redirection, which involves managing file descriptors and process communication.
- **Environment Variable Expansion**: Managing environment variables and supporting their expansion within commands, including the special case of `$?` to represent the exit status of the most recently executed command.
- **Memory Management**: Ensuring efficient memory management throughout the shell, including preventing memory leaks especially in the context of the readline function and dynamically allocated resources.
- **Built-in Commands Implementation**: Creating internal implementations of several built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) that behave consistently with their bash counterparts.
- **Concurrency and Process Management**: Handling concurrency through process creation and management, using system calls like `fork`, `execve`, `wait`, and `pipe`, and ensuring robust process control and signal handling.
- **Error Handling**: Developing comprehensive error handling strategies to deal with invalid commands, permissions issues, nonexistent files, and other runtime errors.

# Team Development Steps for Minishell
## Step 1: Initial Planning and Setup
- **Repository Setup**: Collaboratively set up the GitHub repository, ensuring a clear directory structure and branch strategy.
- **Makefile Creation**: Makefile that includes rules for `all`, `clean`, `fclean`, `re`
- Set up libft libray

## Step 2: Research and Design Phase
### Shell Operations: 
- [What Happens When You Type a Command in Your Terminal](https://www.youtube.com/watch?v=2P7fcVHxA9o&list=LL&index=6) 📹
- [Shell Code Explained](https://www.youtube.com/playlist?list=PLbtzT1TYeoMhF4hcpEiCsOeN13zqrzBJq) 📹

- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) 📹

- [Unix terminals and shells](https://www.youtube.com/playlist?list=PLFAC320731F539902) 📹

- [Terminal vs. Bash vs. Command line vs. Prompt](https://www.youtube.com/watch?v=hMSByvFHOro&ab_channel=LukeSmith) 📝

- [Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/) 📝


### External Functions:
Reviewed the external functions allowed, dividing them among ourselves to research and explain their usage to the team.

#### Readline Functions:
| Function            | Description                                                   |
| ------------------- | ------------------------------------------------------------- |
| `readline`          | Reads a line from the standard input and returns it.         |
| `rl_clear_history`  | Clears the readline history list.                            |
| `rl_on_new_line`    | Prepares readline for reading input on a new line.           |
| `rl_replace_line`   | Replaces the content of the readline current line buffer.    |
| `rl_redisplay`      | Updates the display to reflect changes to the input line.    |
| `add_history`       | Adds the most recent input to the readline history list.     |

#### Standard I/O Functions:
| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `printf`   | Outputs formatted data to stdout.                       |

#### Memory Allocation Functions:
| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `malloc`   | Allocates specified bytes of heap memory.               |
| `free`     | Deallocates previously allocated memory.                |

#### File I/O Functions:
| Function   | Description                                                   |
| ---------- | ------------------------------------------------------------- |
| `write`    | Writes data to a file descriptor.                             |
| `access`   | Checks calling process's permissions for a file or directory. |
| `open`     | Opens a file or device, returning a file descriptor.         |
| `read`     | Reads data from a file descriptor into a buffer.              |
| `close`    | Closes a previously opened file descriptor.                   |

#### Process Control Functions:
| Function      | Description                                                        |
| ------------- | ------------------------------------------------------------------ |
| `fork`        | Creates a new process by duplicating the calling process.         |
| `wait`        | Suspends execution of the calling process until one of its children terminates. |
| `waitpid`     | Waits for a specific child process to change state.               |
| `wait3`       | Waits for any child process to change state.                      |
| `wait4`       | Waits for a specific child process to change state.               |
| `signal`      | Handles or ignores signals sent to the process.                   |
| `sigaction`   | Handles or ignores signals sent to the process.                   |
| `sigemptyset`| Initializes and adds signals to a signal set.                     |
| `sigaddset`   | Initializes and adds signals to a signal set.                     |
| `kill`        | Sends a signal to a process or a group of processes.              |
| `exit`        | Terminates the calling process.                                    |

#### Directory Functions:
| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `getcwd`   | Gets the current working directory.                     |
| `chdir`    | Changes the current working directory.                  |
| `stat`     | Returns information about a file or a file descriptor. |
| `lstat`    | Returns information about a file or a file descriptor. |
| `fstat`    | Returns information about a file or a file descriptor. |
| `unlink`   | Removes a link to a file.                               |
| `execve`   | Replaces the current process image with a new process image. |

#### File Descriptor Functions:
| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `dup`      | Duplicates a file descriptor.                          |
| `dup2`     | Duplicates a file descriptor.                          |
| `pipe`     | Creates a pipe for inter-process communication.        |

#### Directory Functions:
| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `opendir`  | Manages directory streams.                              |
| `readdir`  | Manages directory streams.                              |
| `closedir` | Manages directory streams.                              |

#### Error Handling Functions:
| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `strerror` | Returns a pointer to the textual representation of an error code. |
| `perror`   | Returns a pointer to the textual representation of an error code. |

#### Terminal Functions:
| Function      | Description                                                        |
| ------------- | ------------------------------------------------------------------ |
| `isatty`      | Tests whether a file descriptor refers to a terminal.              |
| `ttyname`     | Returns the name of the terminal associated with a file descriptor.|
| `ttyslot`     | Returns the name of the terminal associated with a file descriptor.|
| `ioctl`       | Controls device-specific input/output operations.                  |
| `getenv`      | Returns the value of an environment variable.                      |
| `tcsetattr`   | Sets and gets terminal attributes.                                 |
| `tcgetattr`   | Sets and gets terminal attributes.                                 |
| `tgetent`     | Terminal handling functions from the termcap library.              |
| `tgetflag`    | Terminal handling functions from the termcap library.              |
| `tgetnum`     | Terminal handling functions from the termcap library.              |
| `tgetstr`     | Terminal handling functions from the termcap library.              |
| `tgoto`       | Terminal handling functions from the termcap library.              |
| `tput`        | Terminal handling functions from the termcap library.              |

## Step 3: Parsing and Input Management

### Command Reading:
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

### Input Parsing Steps:

#### Tokenization 
The goal of the tokenization process is to break down the input string into a series of tokens that the parser can easily understand. These tokens represent commands, arguments, pipes, redirections, and other elements of the shell syntax.

- **Quotations**: Distinguishing between single (`'`) and double (`"`) quotes.
- **Redirections**: Recognizing input (`<`), output (`>`), append (`>>`), and here-documen(`<<`) redirections.
- **Pipes** (`|`): Splitting commands to be executed in a pipeline.
- **Environment variables**: Expanding variables starting with `$`.
- **Command separation**: Identifying commands and their arguments.

#### Token Structure:


```c
// Token type enumeration
typedef enum e_token_type
{
    TOKEN_WORD,      // For commands and arguments
    TOKEN_PIPE,      // For '|'
    TOKEN_REDIR_IN,  // For '<'
    TOKEN_REDIR_OUT, // For '>'
    TOKEN_REDIR_APPEND, // For '>>'
    TOKEN_REDIR_HEREDOC, // For '<<'
    TOKEN_EOF       // For the end of input
}   t_token_type;

// Token structure
typedef struct s_token
{
    t_token_type type;
    char        *value;
    struct s_token *next;
}   t_token;
```

#### Tokenization Strategy:

1. **Whitespace Handling**: Skip whitespace outside quotes to separate commands and arguments.
2. **Quoting**: Correctly handle single (`'`) and double quotes (`"`), preserving the text exactly as is within single quotes and allowing for variable expansion and escaped characters within double quotes.
3. **Redirections and Pipes**: Detect `>`, `>>`, `<`, `<<`, and `|`, treating them as separate tokens while managing any adjacent whitespace.
4. **Variable Expansion**: Identify variables (`$VAR` or `${VAR}`) for later expansion. This might be more related to parsing after tokenization but be aware during tokenization.
5. **Error Handling and Reporting**: Detect and report syntax errors, such as unclosed quotes or other issues.


#### **Tokenization Function**
The tokenization function will iterate through the input string, identifying and categorizing segments according to the shell syntax. 
- `new_token` Function: Allocates and initializes a new token.
- `add_token_to_list` Function: Adds the new token to the end of the tokens list.
- `tokenize_input` Function: Iterates through the input, creating tokens for words separated by spaces.
- `handle_quotes` Function : Handles the quotes in the input string.
- `handle_special_chars` : Handles the special characters in the input string.
- `handle_word` : Handles the words in the input string.

#### Parsing
