# Arbitrary Precision Calculator (DSA Project)

## 📌 Overview
This project implements an "Arbitrary Precision Calculator (APC)" using Linked list. It allows performing mathematical operations on very large numbers that exceed the standard data type limits.

## 🚀 Features
- Supports large integer arithmetic
- Addition, Subtraction, Multiplication, Division , Modulus
- Handles numbers beyond built-in data type limits
- Menu-driven or command-line interface

## 🛠️ Technologies Used
- C Programming Language
- Data Structures (Linked Lists)
- Dynamic Memory Allocation

## 📂 Project Structure
```
APC/
├── main.c
├── addition.c / addition.h
├── subtraction.c / subtraction.h
├── multiplication.c / multiplication.h
├── division.c / division.h
├── modulus.c / modulus.h
├── common.h
└── ...
```

## ⚙️ Compilation
Compile using GCC:

```bash
gcc main.c addition.c subtraction.c multiplication.c division.c -o apc
```

## ▶️ Usage

Run the program:

```bash
./apc
```

Follow the menu to:
- Enter large numbers
- Choose operation (+, -, *, /, %)
- View result

## 📌 Example
Input:
```
Number 1: 987654321987654321
Number 2: 123456789123456789
Operation: +
```

Output:
```
1111111111111111110
```

## ⚠️ Notes
- Designed for very large integers
- Performance depends on number size
- Ensure proper input format

## 👨‍💻 Author
Sai Divakar Busala

## 📄 License
This project is for educational purposes.
