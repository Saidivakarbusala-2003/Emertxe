# Inverted Search (DSA Project)

## 📌 Overview
This project implements an "Inverted Search system" using the DSA. It creates an index of words from multiple files and allows fast searching of words across those files.

## 🚀 Features
- Create an inverted index from multiple text files
- Fast word searching
- Displays files and positions where the word appears
- Menu-driven command-line interface

## 🛠️ Technologies Used
- C Programming Language
- Data Structures (Linked Lists / Hash Tables)
- File Handling

## 📂 Project Structure
```
Inverted_Search/
├── main.c
├── create_db.c / create_db.h
├── search.c / search.h
├── display.c / display.h
├── save.c / save.h
├── update.c / update.h
├── common.h
└── ...
```

## ⚙️ Compilation
Compile using GCC (or) Makefile:

```bash
gcc main.c create_db.c search.c display.c -o inverted_search
```

## ▶️ Usage

### 📥 Create Database
```bash
./inverted_search file1.txt file2.txt file3.txt
```

### 🔍 Search Word
- Enter a word when prompted
- The program displays:
  - File names
  - Word occurrences

## 📌 Example
Search word:
```
data
```

Output:
```
Found in:
file1.txt -> 3 times
file2.txt -> 1 time
```

## ⚠️ Notes
- Works with `.txt` files
- Case sensitivity depends on implementation
- Ensure files exist before execution

## 👨‍💻 Author
Sai Divakar Busala

## 📄 License
This project is open-source and free to use for learning purposes.
