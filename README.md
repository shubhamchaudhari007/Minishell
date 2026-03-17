# 🐚 MiniShell – Custom Linux Shell in C

## 🚀 Overview

MiniShell is a simplified implementation of a Linux shell written in **C**. It acts as a command-line interpreter that reads user input, parses it, and executes commands using Linux system calls.

This project demonstrates core **Operating System concepts** such as process creation, execution, and synchronization.

---

## 🎯 Features

* ✅ Execute system commands (`ls`, `pwd`, `echo`, etc.)
* ✅ Built-in commands: `cd`, `exit`
* ✅ Input parsing and tokenization
* ✅ Process creation using `fork()`
* ✅ Command execution using `exec()` family
* ✅ Parent process synchronization using `wait()`
* ✅ Error handling for invalid commands

---

## 🧠 Concepts Used

* Process Management (`fork`, `exec`, `wait`)
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
│── parser.c
│── execute.c
│── builtins.c
│── headers.h
│── Makefile
```

---

## ▶️ How to Run

### 1. Clone the repository

```bash
git clone https://github.com/your-username/minishell.git
cd minishell
```

### 2. Compile the code

```bash
gcc *.c -o minishell
```

### 3. Run the shell

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
MiniShell$ exit
```

---

## ⚠️ Limitations

* ❌ No pipe (`|`) support
* ❌ No input/output redirection (`>`, `<`)
* ❌ No background execution (`&`)
* ❌ No command history

---

## 🔮 Future Enhancements

* 🔹 Implement piping (`|`)
* 🔹 Add I/O redirection
* 🔹 Support background processes
* 🔹 Add command history feature
* 🔹 Improve error handling and UI

---

## 🧩 Challenges Faced

* Handling process synchronization correctly
* Managing invalid and edge-case inputs
* Debugging segmentation faults
* Designing modular and scalable code

---

## 📚 Learning Outcomes

* Deep understanding of how shells work internally
* Hands-on experience with Linux system calls
* Improved debugging and problem-solving skills
* Strong foundation in system-level programming

---

## 🙏 Acknowledgements

Special thanks to my mentors for their guidance and support throughout this project.

---

## 📌 Author

**Shubham Chaudhari**

---

## 📂 GitHub Repository

👉 https://github.com/your-username/minishell
