# basicLisp
# Lisp Compiler

Welcome to BasicLisp! This is a compiler for the Lisp programming language, designed to transform Lisp code into executable machine code.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Introduction

NOTE: This project was an attempt to learn about compilers and has a hand-written tokenizer, recurrisve descent parser, and code generator all written in c++. This project is ongoing and several features are still missing. If you have questions, feel free to contact me at ericcarroll120@gmail.com

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
    Ensure you have the necessary dependencies installed. This project may require tools like `make`, `gcc`, or specific libraries. For example:
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
./lisp-compiler path/to/yourfile.lisp
```

Or:

```sh
make run
```
