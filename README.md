# 🐚 MiniShell – Custom Linux Shell in C

## 🚀 Overview

MiniShell is a custom implementation of a Linux shell written in **C**. It works as a command-line interpreter that reads user input, parses it, and executes commands using Linux system calls.

This project demonstrates key **Operating System concepts** such as process creation, execution, inter-process communication, and synchronization.

---

## 🎯 Features

* ✅ Execute system commands (`ls`, `pwd`, `echo`, etc.)
* ✅ Built-in commands: `cd`, `exit`
* ✅ Command parsing and tokenization
* ✅ Process creation using `fork()`
* ✅ Command execution using `exec()` family
* ✅ Parent process synchronization using `wait()`
* ✅ Pipe (`|`) support for inter-process communication
* ✅ Background execution (`&`)
* ✅ Error handling for invalid commands

---

## 🧠 Concepts Used

* Process Management (`fork`, `exec`, `wait`)
* Inter-Process Communication (Pipes)
* Linux System Calls
* File Descriptors & I/O Handling
* String Parsing in C
* Command-line Interface Design

---

## ⚙️ Technologies Used

* **Language:** C
* **Platform:** Linux
* **Compiler:** GCC

---

## 🏗️ Project Structure

```
MiniShell/
│── main.c
│── command.c
│── external.c
│── internal.c
│── scan_input.c
│── header.h
│── ext_cmd.txt
│── a.out
```

---

## ▶️ How to Run

### 1. Compile the code

```bash
gcc *.c -o minishell
```

### 2. Run the shell

```bash
./minishell
```

---

## 💻 Sample Usage

```bash
MiniShell$ ls
MiniShell$ pwd
MiniShell$ cd ..
MiniShell$ echo Hello World
MiniShell$ ls | grep .c
MiniShell$ sleep 5 &
MiniShell$ exit
```

---

## ⚠️ Limitations

* ❌ No command history support
* ❌ Limited handling of complex edge cases

---

## 🔮 Future Enhancements

* 🔹 Add command history
* 🔹 Improve error handling
* 🔹 Support environment variables

---

## 🧩 Challenges Faced

* Handling multiple processes with pipes
* Managing background processes efficiently
* Preventing zombie processes
* Debugging segmentation faults and parsing issues

---

## 📚 Learning Outcomes

* Understanding of shell internals
* Hands-on experience with Linux system calls
* Strong debugging and problem-solving skills
* Practical knowledge of process communication

---

## 📌 Author

**Shubham Chaudhari**

---

## 📂 GitHub Repository

👉 https://github.com/shubhamchaudhari007/minishell
