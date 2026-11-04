# lzw 
This is my first real terra project (since the first was two exercices i did in C)

## Description
I made a 16 bits lzw compression in C (only works on text files) but it works! It compresses data into a dictionnary than with magic the file is much smaller

## How to use
The code is already pre-compiled for you! But if you want to modify the code yourself you should install dependecies!

### Install dependecies (for thoses wanting to modify the code)
You will need `make` and `gcc` to compile the code!

#### Windows
Install `MSYS2` that include make and gcc for windows.

1. First install MSYS2
You can get it from msys2's [website](msys2.org)!

2. Open it from the start menu and run
```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
```
press y when prompted

3. Check if there are installed
```bash
gcc --version
make --version
```

#### MacOS
On mac you can use apple's cli tools, they have `make` and `clang` (which is a C compiler that normally will work fine!).

1. First open the terminal
2. Then run 
```bash
xcode-select --install
```
3. Something will pop up, click install 
4. Finally verify
```bash
make --version
clang --version
```

#### Linux
Since linux is goated installing it is so much easier!

**Ubuntu/debian**
```bash
sudo apt install make gcc
```

**Fedora**
```bash
sudo dnf install make gcc
```

**Arch btw**
```bash
sudo pacman -S make gcc
```

Then verify its installed
```bash
make --version
gcc --version
```

### How to use the programs
if you installed the programs from the release open the terminal where the 2 programs are located or cd into it. If you opened the terminal in the folder you can skip step 1.

1. go into the folder
```bash
cd lzw 
```
2. Then run the program
```bash
./lzw [FILE]
```

## What was the hardest step ? 
rewritting the same function for the seconde time and relizing i did everthing wrong again

## License
The project uses the MIT [license](#license).
