![ascii-text-art (3)](https://github.com/zelhajou/42-minishell/assets/39954629/44830c16-9ec2-471f-a075-f6a7e535c0a3)


# Minishell

## Table of Contents

1. [Overview](#overview)
2. [Project Challenges](#project-challenges)
3. [Team Development Steps for Minishell](#team-development-steps-for-minishell)
    1. [Initial Planning and Setup](#step-1-initial-planning-and-setup)
    2. [Research and Design Phase](#step-2-research-and-design-phase)
        1. [Shell Operations](#shell-operations)
        2. [External Functions](#external-functions)
    3. [Parsing and Input Management](#step-3-parsing-and-input-management)
        1. [Command Reading](#command-reading)
        2. [Steps for building the parser and AST (Abstract Syntax Tree)](#steps-for-building-the-parser-and-ast-abstract-syntax-tree)
            1. [Designing a Syntax Error Checker](#designing-a-syntax-error-checker)
            2. [Syntax Error Checker Function](#syntax-error-checker-function)
            3. [Tokenization](#tokenization)
            4. [Token Structure](#token-structure)
            5. [Tokenization Strategy](#tokenization-strategy)
            6. [Tokenization Function](#tokenization-function)
            7. [Parsing](#parsing)
			8. [AST Node Structure](#ast-node-structure)
			9. [Parsing Function](#parsing-function)
			10. [AST Visualization](#ast-visualization)
	4. [Command Execution](#step-4-command-execution)
	5. [Built-in Commands Implementation](#step-5-built-in-commands-implementation)
	6. [Signal Handling](#step-6-signal-handling)
	7. [Environment Variable Expansion](#step-7-environment-variable-expansion)
	8. [Testing and Debugging](#step-8-testing-and-debugging)
4. [Project Structure](#project-structure)
5. [Team Members](#team-members)
6. [Resources](#resources)
7. [Acknowledgements](#acknowledgements)


## Overview

Our Minishell project represents a collaborative effort to build a custom shell program in C, inspired by the functionalities of [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)), the Bourne Again SHell. As part of the 42 School curriculum, this project served as a unique opportunity for us to deepen our collective understanding of system processes, file descriptors, and the complexities of command-line interfaces. Through the development of our own shell, we engaged in a comprehensive exploration of Unix-based systems, gaining hands-on experience in process control, command interpretation, and environmental variable management.

## Project Challenges

- **Parsing User Input**: Accurately parsing user input, including handling spaces, quotes, and special characters, while distinguishing between command arguments and options.
- **Executing Commands**: Implementing logic to search for and execute the right executable based on the PATH environment variable or a specified path, and managing execution of built-in commands versus external commands.
- **Signal Handling**: Correctly handling Unix signals such as SIGINT (`ctrl-C`), SIGQUIT (`ctrl-\`), and EOF (`ctrl-D`), and ensuring the shell behaves similarly to bash in response to these signals.
- **Input/Output Redirection and Pipes**: Implementing input and output redirection (`<`, `>`, `>>`, `<<`) and pipes (`|`) to allow for command chaining and data redirection, which involves managing file descriptors and process communication.
- **Environment Variable Expansion**: Managing environment variables and supporting their expansion within commands, including the special case of `$?` to represent the exit status of the most recently executed command.
- **Memory Management**: Ensuring efficient memory management throughout the shell, including preventing memory leaks especially in the context of the readline function and dynamically allocated resources.
- **Built-in Commands Implementation**: Creating internal implementations of several built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) that behave consistently with their bash counterparts.
- **Concurrency and Process Management**: Handling concurrency through process creation and management, using system calls like `fork`, `execve`, `wait`, and `pipe`, and ensuring robust process control and signal handling.
- **Error Handling**: Developing comprehensive error handling strategies to deal with invalid commands, permissions issues, nonexistent files, and other runtime errors.

## Team Development Steps for Minishell

### Step 1: Initial Planning and Setup

- **Repository Setup**: Collaboratively set up the GitHub repository, ensuring a clear directory structure and branch strategy.
- **Makefile Creation**: Makefile that includes rules for `all`, `clean`, `fclean`, `re`
- Set up libft libray

### Step 2: Research and Design Phase

This phase was about understanding the shell's operations, researching the external functions allowed, and dividing them among ourselves to research and explain their usage to the team.

#### Shell Operations

![shell](https://github.com/user-attachments/assets/730358f1-dd34-49f3-b15f-647bef40c40c)

- [What Happens When You Type a Command in Your Terminal](https://www.youtube.com/watch?v=2P7fcVHxA9o&list=LL&index=6) 📹
- [Shell Code Explained](https://www.youtube.com/playlist?list=PLbtzT1TYeoMhF4hcpEiCsOeN13zqrzBJq) 📹

- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) 📹

- [Unix terminals and shells](https://www.youtube.com/playlist?list=PLFAC320731F539902) 📹

- [Terminal vs. Bash vs. Command line vs. Prompt](https://www.youtube.com/watch?v=hMSByvFHOro&ab_channel=LukeSmith) 📹

![terminals](https://github.com/user-attachments/assets/0296cfe7-6a1d-42c8-ba4c-53419e64cccd)

- [Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/) 📝

#### External Functions

Reviewed the external functions allowed, dividing them among ourselves to research and explain their usage to the team.

**Readline Functions:**

| Function            | Description                                                   |
| ------------------- | ------------------------------------------------------------- |
| `readline`          | Reads a line from the standard input and returns it.         |
| `rl_clear_history`  | Clears the readline history list.                            |
| `rl_on_new_line`    | Prepares readline for reading input on a new line.           |
| `rl_replace_line`   | Replaces the content of the readline current line buffer.    |
| `rl_redisplay`      | Updates the display to reflect changes to the input line.    |
| `add_history`       | Adds the most recent input to the readline history list.     |

**Standard I/O Functions:**

| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `printf`   | Outputs formatted data to stdout.                       |

**Memory Allocation Functions:**

| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `malloc`   | Allocates specified bytes of heap memory.               |
| `free`     | Deallocates previously allocated memory.                |

**File I/O Functions:**

| Function   | Description                                                   |
| ---------- | ------------------------------------------------------------- |
| `write`    | Writes data to a file descriptor.                             |
| `access`   | Checks calling process's permissions for a file or directory. |
| `open`     | Opens a file or device, returning a file descriptor.         |
| `read`     | Reads data from a file descriptor into a buffer.              |
| `close`    | Closes a previously opened file descriptor.                   |

**Process Control Functions:**

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

**Directory Functions:**

| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `getcwd`   | Gets the current working directory.                     |
| `chdir`    | Changes the current working directory.                  |
| `stat`     | Returns information about a file or a file descriptor. |
| `lstat`    | Returns information about a file or a file descriptor. |
| `fstat`    | Returns information about a file or a file descriptor. |
| `unlink`   | Removes a link to a file.                               |
| `execve`   | Replaces the current process image with a new process image. |

**File Descriptor Functions:**

| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `dup`      | Duplicates a file descriptor.                          |
| `dup2`     | Duplicates a file descriptor.                          |
| `pipe`     | Creates a pipe for inter-process communication.        |

**Directory Functions:**
| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `opendir`  | Manages directory streams.                              |
| `readdir`  | Manages directory streams.                              |
| `closedir` | Manages directory streams.                              |

**Error Handling Functions:**
| Function   | Description                                             |
| ---------- | ------------------------------------------------------- |
| `strerror` | Returns a pointer to the textual representation of an error code. |
| `perror`   | Returns a pointer to the textual representation of an error code. |

**Terminal Functions:**
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

### Step 3: Parsing and Input Management

#### Command Reading

**Readline Library**: Implemented readline and integrated add_history ( [GNU Readline](https://en.wikipedia.org/wiki/GNU_Readline))

```bash
brew install readline
```

Add the following to the Makefile:
```makefile
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
INCLUDES = -I./includes -I./lib/libft -I$(READLINE_INCLUDE)
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

### Steps for building the parser and AST (Abstract Syntax Tree)

- **Syntax Error Checking**: This involves verifying whether the input string adheres to the shell's syntax rules. It checks for unclosed quotes, and misuse of redirection or pipe symbols. Syntax error checking ensures that the input can be correctly interpreted and executed.

	![bash-quotes](https://github.com/user-attachments/assets/13f1ff3a-d537-477c-a37e-377a8c29ab5c)

- **Tokenization**: This step breaks the input string into meaningful pieces, known as tokens. Tokens can be commands, arguments, redirection operators (`<`, `>`, `>>`, `<<`), pipe symbols (`|`), and environment variable identifiers. Tokenization simplifies the parsing process by converting the input string into a format that's easier to analyze.
- **Parsing**: During parsing, tokens are analyzed to understand their syntactical relationship. This step involves constructing a representation of the input that reflects the user's intention. Depending on the complexity of the shell, this could mean building an abstract syntax tree (AST) or a simpler structure.
- **AST Construction**:
    - **Commands**: Nodes in the AST represent commands along with their arguments. These nodes are fundamental to understanding what actions the shell needs to perform.
    - **Redirections**: Redirection nodes are created to represent input and output redirections. These nodes are attached to command nodes to modify how the commands read their input or write their output.
    - **Pipelines**: When a pipe is encountered, a pipeline node links command nodes together, indicating that the output of one command serves as the input to another.
    - **Environment Variable Expansion**: This can be handled as part of command parsing or immediately before command execution. It involves replacing environment variable identifiers with their corresponding values.

- **Execution AST**: After the AST is built, it is traversed to execute the commands it represents. This involves:
    - Executing built-in commands directly within the shell.
    - Launching external commands by creating new processes.
    - Setting up redirections as specified by the redirection nodes.
    - Managing pipelines by connecting the stdout of one command to the stdin of the next.

#### a. Designing a Syntax Error Checker

the syntax error checker will be responsible for identifying and reporting syntax errors in the user input.

1. **Unclosed Quotes**: verify that all quotes are properly closed.
2. **Misplaced Operators**: Detect if pipes `|` are used incorrectly, such as being at the start or end of the input, or if multiple pipes are used consecutively.
3. **Logical Operators**: Detect logical operators such as `&&` and `||` and report them as not supported.
4. **Invalid Redirections**: Detect invalid redirections, such as multiple consecutive redirections or redirections at the start or end of the input.

#### b. Syntax Error Checker Function

syntax_checker.c:

- `syntax_error_checker` Function: Iterates through the input string, checking for syntax errors and reporting them if found.
- `has_unclosed_quotes` Function: Checks for unclosed quotes in the input string.
- `has_invalid_redirections` Function: Detects invalid redirections, such as multiple consecutive redirections or redirections at the start or end of the input.
- `has_misplaced_operators` Function: Detects misplaced pipes and redirections.
- `has_logical_operators` Function: Detects logical operators such as `&&` and `||` and reports them as not supported.


#### c. Tokenization

The goal of the tokenization process is to break down the input string into a series of tokens that the parser can easily understand. These tokens represent commands, arguments, pipes, redirections, and other elements of the shell syntax.

- **Quotations**: Distinguishing between single (`'`) and double (`"`) quotes.
- **Redirections**: Recognizing input (`<`), output (`>`), append (`>>`), and here-documen(`<<`) redirections.
- **Pipes** (`|`): Splitting commands to be executed in a pipeline.
- **Environment variables**: Expanding variables starting with `$`.
- **Command separation**: Identifying commands and their arguments.

#### d. Token Structure

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
    TOKEN_ENV_VAR, // For environment variables
}   t_token_type;

// Token structure
typedef struct s_token
{
    t_token_type type;
    char        *value;
    struct s_token *next;
}   t_token;
```

#### e. Tokenization Strategy

1. **Whitespace Handling**: Skip whitespace outside quotes to separate commands and arguments.
2. **Quoting**: Correctly handle single (`'`) and double quotes (`"`), preserving the text exactly as is within single quotes and allowing for variable expansion and escaped characters within double quotes.
3. **Redirections and Pipes**: Detect `>`, `>>`, `<`, `<<`, and `|`, treating them as separate tokens while managing any adjacent whitespace.

#### f. Tokenization Function

The tokenization function will iterate through the input string, identifying and categorizing segments according to the shell syntax.

tokenization.c:

- `tokenize_input` Function: Iterates through the input, creating tokens for words separated by spaces.
- `handle_special_chars` Function: Handles the special characters in the input string.
- `handle_word` Function: Handles the words in the input string.
- `print_tokens` Function: Prints the tokens to verify the tokenization process.

Example:

```bahs
> ls -l | wc -l > output.txt | ls > output2.txt
Token:  ls                    | Type:  WORD                
--------------------------------------------------
Token:  -l                    | Type:  WORD                
--------------------------------------------------
Token:  |                     | Type:  PIPE                
--------------------------------------------------
Token:  wc                    | Type:  WORD                
--------------------------------------------------
Token:  -l                    | Type:  WORD                
--------------------------------------------------
Token:  >                     | Type:  REDIRECT_OUT        
--------------------------------------------------
Token:  output.txt            | Type:  WORD                
--------------------------------------------------
Token:  |                     | Type:  PIPE                
--------------------------------------------------
Token:  ls                    | Type:  WORD                
--------------------------------------------------
Token:  >                     | Type:  REDIRECT_OUT        
--------------------------------------------------
Token:  output2.txt           | Type:  WORD                
--------------------------------------------------
```

#### g. Parsing

The parsing process involves analyzing the tokens to understand their syntactical relationship. This step constructs a representation of the input that reflects the user's intention.

- **Command Parsing**: Parsing commands and their arguments, creating command nodes in the AST.
- **Pipeline Parsing**: Parsing pipeline tokens, creating pipeline nodes in the AST.
- **Redirection Parsing**: Parsing redirection tokens, creating redirection nodes in the AST.
- **File Node Creation**: Creating a file node for redirections in the AST.

#### h .AST Node Structure

The AST node structure will represent the input string in a way that reflects the user's intention. The AST will be composed of nodes that represent commands, arguments, redirections, and pipelines.

```c
typedef struct s_ast_node
{
    t_node type type;
    char *args;
    struct s_ast_node *left;
    struct s_ast_node *right;
}   t_ast_node;
```

#### i. Parsing Function

The parsing function will iterate through the tokens, building an abstract syntax tree (AST) that represents the input string.

parse.c:

- `parse_tokens` Function: Iterates through the tokens, building an abstract syntax tree (AST) that represents the input string.
- `parse_command` Function: Parses a command and its arguments, creating a command node in the AST.
- `parse_pipeline` Function: Parses pipeline tokens, creating pipeline nodes in the AST.
- `parse_redirection` Function: Parses redirection tokens, creating redirection nodes in the AST.
- `create_file_node` Function: Creates a file node for redirections in the AST.

#### j. AST Visualization

generate_ast_diagram/generate_ast_diagram.c:

- `generate_ast_diagram` Function: Generates a visual representation of the AST, showing the structure of the input string.

Example:
```bash
ls -l | wc -l > output.txt | ls > output2.txt
```

![graphviz](https://github.com/zelhajou/42-minishell/assets/39954629/e8cbd784-3ee1-4642-803c-3b903cbb7afe)

[GraphvizOnline](https://dreampuf.github.io/GraphvizOnline/#digraph%20AST%20%7B%0A%220x7ff812f05540%22%20%5Blabel%3D%22%7C%22%5D%3B%0A%220x7ff812f05540%22%20-%3E%20%220x7ff812f05560%22%20%5Blabel%3D%22L%22%5D%3B%0A%220x7ff812f05560%22%20%5Blabel%3D%22CMD%3A%20ls%20-l%22%5D%3B%0A%220x7ff812f05540%22%20-%3E%20%220x7ff812f05360%22%20%5Blabel%3D%22R%22%5D%3B%0A%220x7ff812f05360%22%20%5Blabel%3D%22%7C%22%5D%3B%0A%220x7ff812f05360%22%20-%3E%20%220x7ff812f05300%22%20%5Blabel%3D%22L%22%5D%3B%0A%220x7ff812f05300%22%20%5Blabel%3D%22REDIR%3A%20%22%5D%3B%0A%220x7ff812f05300%22%20-%3E%20%220x7ff812f05320%22%20%5Blabel%3D%22L%22%5D%3B%0A%220x7ff812f05320%22%20%5Blabel%3D%22CMD%3A%20wc%20-l%22%5D%3B%0A%220x7ff812f05300%22%20-%3E%20%220x7ff812f053f0%22%20%5Blabel%3D%22R%22%5D%3B%0A%220x7ff812f053f0%22%20%5Blabel%3D%22CMD%3A%20output.txt%22%5D%3B%0A%220x7ff812f05360%22%20-%3E%20%220x7ff812f05420%22%20%5Blabel%3D%22R%22%5D%3B%0A%220x7ff812f05420%22%20%5Blabel%3D%22REDIR%3A%20%22%5D%3B%0A%220x7ff812f05420%22%20-%3E%20%220x7ff812f05450%22%20%5Blabel%3D%22L%22%5D%3B%0A%220x7ff812f05450%22%20%5Blabel%3D%22CMD%3A%20ls%22%5D%3B%0A%220x7ff812f05420%22%20-%3E%20%220x7ff812f054b0%22%20%5Blabel%3D%22R%22%5D%3B%0A%220x7ff812f054b0%22%20%5Blabel%3D%22CMD%3A%20output2.txt%22%5D%3B%0A%7D%0A)

### Step 4: Command Execution

- **Built-in Commands**: Implementing internal versions of several built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) that behave consistently with their bash counterparts.
  
	![builtins](https://github.com/user-attachments/assets/ce5fba5b-96bc-44d8-88be-b5a39b0b362e)

- **External Commands**: Implementing logic to search for and execute the right executable based on the PATH environment variable or a specified path.
  
	![path](https://github.com/user-attachments/assets/88709685-dfae-49c5-85e6-e4d45f0a1dd9)

- **Process Creation**: Using system calls like `fork`, `execve`, `wait`, and `pipe` to manage process creation and execution.

	![processes (1)](https://github.com/user-attachments/assets/5c7a2793-78ff-4dd5-bd01-a208457fd9cf)

- **Redirection and Pipes**: Implementing input and output redirection (`<`, `>`, `>>`, `<<`) and pipes (`|`) to allow for command chaining and data redirection.
  
	![redirects](https://github.com/user-attachments/assets/cc07277b-2fe0-425a-ba39-0013f9871d1c)
	![pipes](https://github.com/user-attachments/assets/3cbc7f85-53e7-4312-bf3d-1b9053533ece)
	![bash-pipes](https://github.com/user-attachments/assets/90379cd6-43f8-44f6-b089-958bed58a3a9)

### Step 5: Built-in Commands Implementation

![builtins](https://github.com/user-attachments/assets/ce5fba5b-96bc-44d8-88be-b5a39b0b362e)

- **echo**: Outputs the arguments passed to it.
- **cd**: Changes the current working directory.
- **pwd**: Prints the current working directory.
- **export**: Sets environment variables.
- **unset**: Unsets environment variables
- **env**: Prints the environment variables.
  
  	![environment-variables](https://github.com/user-attachments/assets/87e4570b-e029-4f0e-a38c-f31837e0612e)
  
- **exit**: Exits the shell.

### Step 6: Signal Handling

![signals](https://github.com/user-attachments/assets/308b83ea-ad8f-4bcd-ba32-0cf79bf1b71f)

- **SIGINT**: Handling the `ctrl-C` signal to interrupt the shell's execution.
- **SIGQUIT**: Handling the `ctrl-\` signal to quit the shell.
- **EOF**: Handling the `ctrl-D` signal to exit the shell.

### Step 7: Environment Variable Expansion

- **Environment Variable Expansion**: Managing environment variables and supporting their expansion within commands, including the special case of `$?` to represent the exit status of the most recently executed command.
  
	![parameter-expansion](https://github.com/user-attachments/assets/c1824c1c-7d2a-4244-ae4c-e95d063c4a45)

### Step 8: Testing and Debugging

- [reda ghouzraf](https://github.com/rghouzra) : The most skilled human tester in the world
- [Minishell Tests](https://docs.google.com/spreadsheets/d/1BLU6C9S7aoCl01x74GiW7s4xpEWWJ1cPrMTcLwISruk/edit#gid=1627853444)
- <https://github.com/Pyr-0/Minishell-42/wiki/edge-(or-non-edge)-cases-to-test-out>
- <https://github.com/nicolasgasco/42_minishell/blob/main/test_cases.txt>


## Project Structure

```bash
├── includes
│   └── minishell.h
├── lib
│   └── libft
├── Makefile
└── src
    ├── 01_input_validation
    ├── 02_tokenization
    ├── 03_parsing
    ├── 04_execution
    ├── 05_builtin
    ├── 06_signals
    ├── 07_env_var_expansion
    ├── main.c
    └── utils
```

## Team Members

- [Bilal Edd](https://github.com/edbilal)
- [Zakaria Elhajoui](https://github.com/zelhajou)

## Resources

- <https://www.gnu.org/software/bash/manual/html_node/Definitions.html#index-name>
- <https://www.youtube.com/watch?v=S2W3SXGPVyU&ab_channel=theroadmap>
- <https://tomassetti.me/guide-parsing-algorithms-terminology/>
- <https://github.com/os-moussao/Recursive-Descent-Parser/tree/master>
- <https://minishell.simple.ink/>
- <https://github.com/iciamyplant/Minishell>

## Acknowledgements

Thanks to [reda ghouzraf](https://github.com/rghouzra), [MTRX](https://github.com/whoismtrx), [Nasreddine hanafi](https://github.com/Nx21), [Khalid zerri](https://github.com/zerrikhalid) for their help and support during the project.
