# LSB Image Steganography (C Project)

## 📌 Overview
This project implements "Least Significant Bit (LSB) Image Steganography" using the C programming language. It allows users to hide and extract secret messages within BMP image files.

## 🚀 Features
- Encode secret text into BMP images
- Decode hidden messages from steganographic images
- Works with uncompressed `.bmp` files
- Simple command-line interface

## 🛠️ Technologies Used
- C Programming Language
- File Handling
- Bit Manipulation

## 📂 Project Structure
```
Lsb_Steganography/
├── main.c
├── encode.c / encode.h
├── decode.c / decode.h
├── common.h
├── types.h
├── secret.txt
├── steged_img.bmp
└── ...
```

## ⚙️ Compilation
Use GCC to compile the project:

```bash
gcc main.c encode.c decode.c -o stego
```

## ▶️ Usage

### 🔐 Encoding
Hide a secret message inside an image:

```bash
./stego -e beautiful.bmp secret.txt output.bmp
```

### 🔓 Decoding
Extract the hidden message:

```bash
./stego -d output.bmp decoded.txt
```

## 📌 Example
- Input image: `beautiful.bmp`
- Secret message file: `secret.txt`
- Output image: `steged_img.bmp`

## ⚠️ Notes
- Only BMP images are supported
- Ensure the image is large enough to hold the secret data

## 👨‍💻 Author
Sai Divakar Busala

## 📄 License
This project is open-source and free to use for learning purposes.
