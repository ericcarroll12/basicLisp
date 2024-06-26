# basicLisp
# Lisp Compiler

Welcome to BasicLisp! This is a compiler for the Lisp programming language, designed to transform Lisp code into executable machine code.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## Introduction

NOTE: This project is an attempt to learn about compilers and has a hand-written tokenizer, recurrisve descent parser, and code generator all written in c++. This project is ongoing and several features are still missing. If you have questions or suggestions, feel free to contact me at ericcarroll120@gmail.com

## Features

- Parsing Lisp syntax
- Semantic analysis
- Code generation
- Optimizations for performance

## Installation

To install and set up the Lisp Compiler on your local machine, follow these steps:

1. **Clone the repository**
    ```sh
    git clone https://github.com/ericcarroll12/basicLisp.git
    cd basicLisp
    ```

2. **Install dependencies**
    The only dependencies are `make` and `gcc`. the rest is hand-written
    ```sh
    sudo apt-get install make gcc
    ```

3. **Build the project**
    ```sh
    make
    ```

## Usage

After building the project, you can use the compiler to compile Lisp files:

```sh
./basicLisp path/to/yourfile.lisp
```

Or:

```sh
make run
```
