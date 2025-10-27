# Pipex

A C implementation that reproduces the shell pipe functionality (`|`) as seen in Unix/Linux systems.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
  - [Mandatory Part](#mandatory-part)
  - [Bonus Part](#bonus-part)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Author](#author)

## 🎯 Overview

Pipex is a project from the 42 School curriculum that challenges students to understand and implement the pipe mechanism used in Unix shells. The program takes an input file, executes two commands in sequence where the output of the first command becomes the input of the second command, and writes the final result to an output file.

The project is equivalent to the shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

## ✨ Features

### Mandatory Part
- **Two-command pipeline**: Execute two commands with pipe communication
- **File redirection**: Read from input file and write to output file
- **Error handling**: Proper error management for file access, command execution, and system calls
- **Memory management**: No memory leaks, proper cleanup of resources

### Bonus Part
- **Multiple pipes**: Support for unlimited number of commands
- **Here_doc functionality**: Implement `<< LIMITER` functionality
- **Advanced pipeline**: Chain multiple commands together

## 🚀 Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/itsfwenk/pipex_vog.git
   cd pipex_vog
   ```

2. **Compile the project:**
   ```bash
   # For mandatory version
   make

   # For bonus version
   make bonus
   ```

3. **Clean up (optional):**
   ```bash
   make clean    # Remove object files
   make fclean   # Remove object files and executable
   make re       # Clean and recompile
   ```

## 📖 Usage

### Mandatory Part

```bash
./pipex file1 cmd1 cmd2 file2
```

**Parameters:**
- `file1`: Input file to read from
- `cmd1`: First command to execute
- `cmd2`: Second command to execute
- `file2`: Output file to write results

**Shell equivalent:**
```bash
< file1 cmd1 | cmd2 > file2
```

### Bonus Part

#### Multiple pipes:
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
```

**Shell equivalent:**
```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdN > file2
```

#### Here_doc mode:
```bash
./pipex here_doc LIMITER cmd1 cmd2 file
```

**Shell equivalent:**
```bash
cmd1 << LIMITER | cmd2 >> file
```

## 💡 Examples

### Basic Usage
```bash
# Count lines in a file and display first 3
./pipex input.txt "grep hello" "wc -l" output.txt

# Shell equivalent:
# < input.txt grep hello | wc -l > output.txt
```

### Multiple Commands (Bonus)
```bash
# Complex pipeline with multiple commands
./pipex input.txt "cat" "grep pattern" "sort" "uniq -c" output.txt

# Shell equivalent:
# < input.txt cat | grep pattern | sort | uniq -c > output.txt
```

### Here_doc Example (Bonus)
```bash
# Using here_doc functionality
./pipex here_doc EOF "grep hello" "wc -l" output.txt
# Then type your input and end with 'EOF'

# Shell equivalent:
# grep hello << EOF | wc -l >> output.txt
```

## 📁 Project Structure

```
pipex_vog/
├── Makefile                    # Build configuration
├── README.md                   # Project documentation
├── includes/                   # Header files
│   ├── pipex.h                # Mandatory part headers
│   ├── pipex_bonus.h          # Bonus part headers
│   ├── libft.h                # Libft library headers
│   └── get_next_line.h        # GNL headers for bonus
├── mandatory/                  # Mandatory implementation
│   ├── pipex.c                # Main program
│   ├── cmd1_manager.c         # First command management
│   ├── last_cmd_manager.c     # Last command management
│   ├── fd_manager.c           # File descriptor management
│   ├── pid_manager.c          # Process management
│   ├── pipex_utils.c          # Utility functions
│   ├── protector.c            # Error handling
│   ├── ft_dprintf.c           # Custom printf implementation
│   └── ft_strjoin_pipex.c     # Custom string joining
├── bonus/                      # Bonus implementation
│   ├── main_bonus.c           # Main program with bonus features
│   ├── here_doc_manager_bonus.c # Here_doc functionality
│   ├── middle_cmd_manager_bonus.c # Middle commands management
│   ├── get_next_line_bonus.c  # Line reading for here_doc
│   └── [other bonus files]    # Extended functionality
└── libft/                      # Custom C library
    └── [libft files]          # Standard library functions
```

## 🔧 Technical Details

### Key Concepts Implemented

1. **Process Management**:
   - Fork processes for each command
   - Proper parent-child process communication
   - Wait for child processes and handle exit status

2. **Pipe Communication**:
   - Create pipes between processes
   - Proper file descriptor management
   - Handle input/output redirection

3. **Command Execution**:
   - Parse command arguments
   - Find executable paths using PATH environment variable
   - Execute commands with `execve()`

4. **Error Handling**:
   - Check for file permissions and existence
   - Handle command not found errors
   - Proper error messages and exit codes

5. **Memory Management**:
   - Dynamic memory allocation and deallocation
   - Prevent memory leaks
   - Clean resource management

### System Calls Used
- `pipe()` - Create pipe for inter-process communication
- `fork()` - Create child processes
- `execve()` - Execute commands
- `wait()`/`waitpid()` - Wait for child processes
- `open()`/`close()` - File operations
- `dup2()` - Duplicate file descriptors
- `access()` - Check file permissions

### Compilation Flags
- `-Wall -Werror -Wextra`: Strict warning and error handling
- `-g3`: Debug information for development

## 👨‍💻 Author

**fli** - 42 School Student
- GitHub: [@itsfwenk](https://github.com/itsfwenk)
- Email: fli@student.42.fr

---

*This project is part of the 42 School curriculum, focusing on system programming, process management, and understanding Unix pipes.*
