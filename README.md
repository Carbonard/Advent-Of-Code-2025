# 🎄 Advent of Code

This repository contains my own solutions to the This repository contains my own solutions to [Advent of Code](https://adventofcode.com/2025) (2025). The subjects to the problems can be found on the official page [https://adventofcode.com/2025](https://adventofcode.com/2025).

It's organized by days, each one having two parts (except day 12) and its own Makefile. There is also a global Makefile that compiles and runs any part of any day.

### 🗂️ Description
---

- **dayXX/**  
  Contains the solution for the corresponding Advent of Code day.
  Each folder has its own Makefile and supports:
  - `part_1`
  - `part_2`

- **libft/**  
  Personal library with reusable utility functions.

- **dynamic_arrays/**  
  Personal library for handling dynamic arrays.

- **Root Makefile**  
  Main Makefile that acts as a dispatcher to build any day and part.


## 🛠️ Build and Usage

### 📌 Build a specific day

```bash
make dayXX
```
By default, this builds part 1.

Example:

```bash
make day01
```

### 📌 Build a specific part

You can specify the part using the `PART` variable:

```bash
make dayXX PART=part_2
```

Example:

```bash
make day03 PART=part_2
```

## 🧹 Clean

To remove all generated binaries and build files:

```bash
make clean
```

## 📚 Dependencies

For some days (02, 05 and 06) I wanted to practice with the C library
 - gmp
 
For installing on Debian/Unbuntu :
```bash
sudo apt install libgmp-dev
```
This project also uses custom libraries:

- libft
- dynamic_arrays

Both are built automatically when compiling any day.
