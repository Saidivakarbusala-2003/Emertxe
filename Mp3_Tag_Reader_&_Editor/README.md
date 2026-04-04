# MP3 Tag Reader & Editor (C Project)

## 📌 Overview
This project is a **MP3 Tag Reader and Editor** built using the C programming language. It allows users to read and modify metadata (ID3 tags) of MP3 files such as title, artist, album, and more.

## 🚀 Features
- Read MP3 metadata (ID3 tags)
- Edit tags like:
  - Title
  - Artist
  - Album
  - Year
  - Genre
- Command-line interface for easy interaction
- Works with standard MP3 files

## 🛠️ Technologies Used
- C Programming Language
- File Handling
- Structures & Pointers
- Binary File Processing

## 📂 Project Structure
```
Mp3_Tag_Reader_Editor/
├── main.c
├── read.c / read.h
├── edit.c / edit.h
├── common.h
├── types.h
└── ...
```

## ⚙️ Compilation
Compile using GCC:

```bash
gcc main.c read.c edit.c -o mp3tag
```

## ▶️ Usage

### 📖 Read Tags
```bash
./mp3tag -r sample.mp3
```

### ✏️ Edit Tags
```bash
./mp3tag -e -t "New Title" sample.mp3
./mp3tag -e -a "Artist Name" sample.mp3
./mp3tag -e -A "Album Name" sample.mp3
```

## 📌 Example
- Input file: `sample.mp3`
- Modify metadata fields via command line

## ⚠️ Notes
- Ensure the MP3 file has ID3 tags
- Backup original file before editing

## 👨‍💻 Author
Sai Divakar Busala

## 📄 License
This project is open-source and free to use for learning purposes.
