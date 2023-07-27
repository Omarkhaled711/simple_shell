# ALX Simple Shell Project

This project is a simple implementation of a shell program, written in C. The program allows users to execute commands and navigate the file system using a command-line interface.

## Screenshots

![Screenshot 1](/screenshots/screenshot1.png)

![Screenshot 2](/screenshots/screenshot2.png)

![Screenshot 2](/screenshots/screenshot3.png)

## Design

The ALX simple shell project is designed to use a struct called `Shell_Info` to hold information about the shell. The struct contains fields for the command-line arguments, input, output, status, environment variables, and process ID.

The project processes user input in a structured manner, with the `start_loop` function handling the main loop of the program. The function reads user input using the `getline` function and checks whether the input is valid. If it is, the program splits the input into separate commands and executes them. If the input is not valid, the program returns an error message to the user.

The project also uses several helper functions to parse and process user input. The `initialize_shell_info` function initializes the `Shell_Info` struct, while the `remove_comments` function removes any comments from the user input. The `check_syntax_error` function checks for syntax errors in the user input,and so on

## Getting Started

To use the ALX simple shell program, you first need to clone the repository to your local machine:

```
$ git clone https://github.com/<username>/simple_shell.git
```

Once you have the repository, you can compile the program using the following command:

```
$ gcc -Wall -Werror -Wextra -pedantic *.c -o hsh.out
```

To run the program, simply type the following command:

```
$ ./hsh.out
```

## Usage

The ALX simple shell program is designed to be used with the command-line interface. Users can execute commands and navigate the file system using the following commands, and more:

- `ls` - list directory contents
- `echo` - display a message
- `cat` - concatenate and display files
- `exit` - exit the shell program
- `env` - prints the environment variables

To execute a command, simply type the command name followed by any necessary arguments. For example:

```
$ ls -l
```
To exit the shell, simply press CTRL + D

## Credits

This project was part of ALX software engineering track
