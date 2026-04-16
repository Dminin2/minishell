*This project has been created as part of the 42 curriculum by aomatsud and hmaruyam.*

# Minishell

## Description
Minishell is a simplified implementation of a Unix shell, inspired by Bash.
The goal of this project is to understand how shells work internally by handling processes, file descriptors, and command execution.

This shell provides an interactive command-line interface where users can execute commands, manage environment variables, and use features such as pipes and redirections.

Through this project, we explore:
- Process creation and management (`fork`, `execve`, `wait`)
- File descriptor manipulation (`dup`, `pipe`)
- Signal handling
- Parsing and interpreting user input

## Features

### Mandatory Features
- Display a prompt and wait for user input
- Command history using `readline`
- Execution of commands using PATH, relative, or absolute paths
- Handling of quotes:
  - `'` (single quotes)
  - `"` (double quotes)
- Environment variable expansion (`$VAR`, `$?`)
- Redirections:
  - `<` input redirection
  - `>` output redirection
  - `>>` append output
  - `<<` heredoc
- Pipes (`|`)
- Signal handling:
  - `Ctrl+C` → new prompt
  - `Ctrl+D` → exit
  - `Ctrl+\` → ignored
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Instructions

### Requirements
- Language: C
- Compiler: `cc`
- Flags: `-Wall -Wextra -Werror`

### Compilation
```bash
make
```

### Run
```bash
./minishell
```

### Clean
```bash
make clean
make fclean
```

### Usage
Once the program is launched, you can type commands just like in Bash:
```bash
minishell$ ls -l
minishell$ echo "Hello world"
minishell$ cat file.txt | grep hello
minishell$ export PATH=/usr/bin
minishell$ echo hello > file.txt
minishell$ cat < file.txt
minishell$ ls | grep minishell
```

## Technical Design

The project is structured into several components:
- Lexer / Parser
  - Tokenizes user input
  - Handles quotes and environment variables
- Executor
  - Executes commands using fork and execve
  - Manages pipes and redirections
- Builtins
  - Handles internal commands without spawning a new process
- Signals
  - Custom signal handlers to mimic Bash behavior
- Environment Management
  - Stores and updates environment variables

### CI / Automation
- Automated build and validation using GitHub Actions
- Integrated checks such as compilation and memory validation

## References

### References
Bash manual
https://www.gnu.org/software/bash/manual/bash.html

### About AI Usage
This project was developed with the assistance of AI tools as coding support.

- System design, architecture, and feature decisions were made by the developer.
- AI was used to:
  - Code review
  - Debugging
- All final code and logic were reviewed and fully understood by the developer.

## Notes

- Memory leaks are carefully managed (except those allowed by readline)
- Behavior is designed to be close to Bash, but only within the scope of the subject
- Undefined behaviors outside the subject are not handled
