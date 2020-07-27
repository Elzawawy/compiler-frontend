<h1 align='center'>Language-Independent Compiler Frontend</h1>

<p align='center'>
  <img src="https://media.geeksforgeeks.org/wp-content/cdn-uploads/1-34.png"/>
</p>

Frontend phases of a language-independent compiler, that takes in language specifications, source code, and emits a parse tree for the code, and any errors found. This is a project developed for the PLT (Programming Language Translation) course at Faculty of Engineering, Alexandria University in Spring 2020 Offering. 

## Project Objectives And Goals Achieved

* Be able to build a compiler for a (simplified) programming language.
* Study the theory behind compilers and langugaes translation.
* Know how to use compiler construction tools, such as generators of scanners and parsers.
* Practice how to work on a large software project: using Agile Project managment (Check the Github Projects on Repository) and clean git branching/PR model.
* Experience using C++ heavily where the compiler phases is fully developed in C++ language.

## Project Overview 

* We built the first two phases of the compiler frontend (Follow links):
  * [Lexical Analysis Generator](./lexgen)
  * [Syntatic Analysis Generator](./prsgen)

In each of the directories, is the source code of each module separted with it's unit test cases and documentation. Refer to each README inside the directories to get to know each phase well and how to use it. Both phases are run in one pass only, to avoid multiple and wasted computations. 

The **input** to the program is three files: 
* Language Grammar Specifiction.
* Language Tokens/Terminals Specification.
* Source code (follows the above two files).

The **output** of the program is as follows: 
* A representation of the parse the of the source code.
* Tokens recognized in the source code. 
* Any errors found in the source code.


<h3 align='center'>Made with :heart:</h3>
