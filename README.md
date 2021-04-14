# Simple Shell
Shell is a program written by Ken Thompson in 1971, that takes the command inputs written from the the user’s keyboard and passes them to the machine to execute them through the kernel. It also verifies if the command inputs from the user are correct.

## Getting Started

* [Ubuntu 14.04 LTS](http://releases.ubuntu.com/14.04/) - Operating system reqd.

* [GCC 4.8.4](https://gcc.gnu.org/gcc-4.8/) - Compiler used

## Installation
Clone the repository into a new directory
```bash
git clone https://github.com/csoriano2832/simple_shell.git
```
Compile:
```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```
Execute:
```bash
./shell
```
or in non-interactive mode:
```bash
echo "ls" | ./shell
```
## Example of Use (FIX IT)
```bash
vagrant@vagrant-ubuntu-trusty-64:~/simple_shell$ ./hsh
$ ls -l
total 28
-rw-rw-r-- 1 vagrant vagrant  167 Apr 13 16:21 AUTHORS
-rw-rw-r-- 1 vagrant vagrant 1667 Apr 14 17:09 getenv.c
-rw-rw-r-- 1 vagrant vagrant 1347 Apr 13 16:21 man_1_simple_shell
-rw-rw-r-- 1 vagrant vagrant 1934 Apr 13 16:28 README.md
-rw-rw-r-- 1 vagrant vagrant 2775 Apr 14 17:09 shell.c
-rw-rw-r-- 1 vagrant vagrant  567 Apr 14 17:09 shell.h
-rw-rw-r-- 1 vagrant vagrant 1505 Apr 14 17:09 strings.c
$
```

### Files 

| File Name | Description |
| ------ | ------ |
| shell.c | Executes programs, verify the locations and handles all functions. |
| string.c | Functions for string manipulation:
|_puts | Writes a string of characters to stdout |
|_strlen | Counts the length of a string |
|_strcmp | Compares characters in two strings|
|_putchar | Writes a single character to stdout |
| shell.h | Libraries and prototypes of functions |
| getenv.c | searches for any existing environment variable |


### Authors

Christopher Soriano | [GitHub](https://github.com/csoriano2832)

Oscar Ochart | [GitHub](https://github.com/ElOchi)

License
MIT - http://www.opensource.org/licenses/mit-license.php
