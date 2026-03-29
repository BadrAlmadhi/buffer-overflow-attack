# Buffer Overflow Attack Assignment

## 1. Program Overview

This program reads a password from a file called `password.txt` and checks if it matches the correct password `"superSecretPassword"`.

- If the password is correct → the program calls `success()` and opens a shell
- If the password is incorrect → the program calls `failure()` and prints an error message

The main function calls `login()` and uses its return value to decide which function to execute.

---

## 2. Function Explanation

### login()

- Declares a local buffer: `char password[48]`
- Opens `password.txt` for reading
- Reads file content into the buffer using `read()`
- Returns the result of `check_secret1()`

### check_secret()

- Compares the input password with `"superSecretPassword"`
- Ensures:
  - The length matches exactly
  - The content matches exactly using `memcmp()`

### check_secret1()

- Simply calls `check_secret()`

### success()

- Prints `"successful login!"`
- Executes `/bin/sh` using `execve()`
- Replaces the program with a shell

### failure()

- Prints `"wrong password"`

---

## 3. Vulnerability Explanation

The program contains a **stack buffer overflow vulnerability** in the `login()` function:

```c
char password[48];
int pwLen = read(fd, password, 1000);

```
## 4. Stack layout 

Higher memory

| Return address |
| Other local variables |
| password[48] |
| RSP (stack pointer)| 

Lower memory


