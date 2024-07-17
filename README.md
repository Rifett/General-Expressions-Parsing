# General Expressions Parsing

## Overview 
This project is my Bachelor Thesis, centered around the topic of **General Expressions** parsing and a possibility of parsing whole programming languages using General Expressions. 

## Contents
- Bachelor Thesis paper (levinale-thesis.pdf)
- Presentation for a short preview (Thesis_Presentation.pdf)
- Proof-of-Concept codebase (All the rest)
 
## Codebase

### Structure
- **AtomicParsingOp**
- **ParsedStorage**
- **ParsingLayers**
  - **ParsingLayer**
- **TableParser**
- **Tokenizer**


### Description
According to the format of General Expressions, to parse something we must create an operators' priority table (*ParsingLayers*), 
inside of which there will be different layers (*ParsingLayer*) that would be represented by a certain set of operators (*AtomicParsingOp*). 
All these elements are required to build a parser (*TableParser*), along with helper structure of a temporary storage for parsed elements (*ParsedStorage*).
To simplify parsing process, a custom tokenizer (*Tokenizer*) has to be provided.

## Things to be done later and better
- The testing of the Thesis elements were done in a bit of a hurry, so they are just divided into two sections by the comments (*General testing* and *Pascal testing* accordingly), so they are to be properly reorganized.
- Also, the codebase was initially meant to be just a Proof-of-Concept, so there are no proper comments and the code organization can be improved in general.
- Additionally, datatype checking can be added, in order to test and develop one of the Thesis results.

## Summary
In order to get a brief understanding of the Thesis, it is enough to just go quickly through the presentation. 
However, there are quiet a lot of details, to understand which it is recommended to read the full thesis paper.

## Contact
For any questions or feedback, feel free to contact me via my email: levinale17@gmail.com.
