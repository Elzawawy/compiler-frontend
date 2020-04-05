# LEXGEN (LAG)

LEXGEN or as we like to call it LAG (**L**exical **A**nalyzer **G**enerator) is **phase 1** assignment of a **compiler frontend pipeline**. This work is done as the project for PLT (**P**rogramming **L**anguage **T**ranslation) course at Alexandria University, Faculty of Engineering Computer and Communications Department, offered in Spring 2020.

<p align='center'>
<img src="./images/1.png"/>
</p>

**But, What's LAG really ?**

A LAG's objective is to produce a lexical analyzer automatically by specifying the lexeme patterns. This approach makes it easier to modify a lexical analyzer, since we have only to rewrite the affected patterns, not the entire program. It also speeds up the process of implementing the lexical analyzer, since the programmer specifies the software at the very high level of patterns and relies on the generator to produce the detailed code.

<p align='center'><img src="./images/2.png"/></p>

We begin the documentation of our LAG by explaining the first component, the **language parser** with giving a brief about regular expressions, a convenient notation for specifying lexeme patterns then show how did we transform this notation into *nondeterministic automata* using **NFA** component
and then into *deterministic automata* using **DFA** component to feed into another component which is the **Minimal DFA** component

We lastly explain the last component of our LAG which is a **driver**, that is, code which simulates these automata and uses them as a guide to determining the next token. This driver and the specification of the automaton form the nucleus of the lexical analyzer.

## Component 1: Language Parser

- In other words, it is the lexical rules file reader, that parses lexemes specification.

- Takes an input file with format specified in requirements document.

- Emits an output with (Table of Inputs & List of Regular Expressions).

### Background: RE (Regular Expressions)

<p align='center'><img src="./images/3.png"/></p>

- A convenient notation for specifying lexeme patterns.
- While they cannot express all possible patterns, they are very effective in specifying those types of patterns that we actually need for tokens.
- Regular expressions notation has come into common use for describing all the languages that can be built from language operators applied to the symbols of some alphabet.
- Each regular expression r denotes a language L(r), which is also defined recursively from the languages denoted by r's sub-expressions.
- Regular expressions often contain unnecessary pairs of parentheses. We may drop certain pairs of parentheses if we adopt the conventions that:

  - The **unary operator** `*` has highest precedence and is left associative.
  - **Concatenation** has second highest precedence and is left associative.
  - **Union** `|` has lowest precedence and is left associative.
  - We may replace the regular expression `(a)|((b)\*(c))` by `a|b\*c.`

- A language that can be defined by a regular expression is called a **regular set**. If two regular expressions r and s denote the same regular set, we say they are equivalent and write r = s.

### Background: RD (Regular Definitions)

- We may wish to give names to certain regular expressions and use those names in subsequent expressions, as if the names were themselves symbols.

### Language Lexical Rules Input File Format

- No specific extension for the file is required. But should only contain ASCII characters.

- *Regular definitions* are lines in the form **LHS = RHS**.

- *Regular expressions* are lines in the form **LHS: RHS**.
- Note that `:` and `=` are not reserved by the rules 
- **Keywords** are enclosed by **`{ }`** in separate lines and a *space* between each keyword in the list.

- **Punctuations** are enclosed by **`[ ]`** in separate lines and a *space* between each punctuation in the list.

- **`\L`** represents *Lambda* symbol.

- **Supported Operations: `-` `|` `+` `*` `(` `)`**
- Any reserved symbol from the previous needed to be used within the language itself, is preceded by an **escape backslash character** `\` .

### Implementation Details

Two classes resembles this component work.

- RegularExpression
- LanguageParser

**RegularExpression** class resembles the RE entity we described a brief about it above.

- Use `RegularExpression regex(name, value);` to create an instance of the class.

- Use `regex.applyRangeOperationIfExists()` to enumerate the range operation and expand it into multiple union operators.

- Use `regex.extractInputSymbols()` to retrieve the input symbols available from the regex in an `unordered_set` of strings.

- Use `getName()` and `getValue()` to retrieve the params of this regex at any time.

**LanguageParser** class resembles the RE entity we described a brief about it above.

- Use `LanguageParser parser();` to create an instance of the class.

- Use `parser.parseFile(filepath)` to parse a language lexical rules file and convert it into the two following data-structures:

  - `unordered_set<string> InputTable`
  - `vector<RegularExpression> Expressions`

- Use `parser.getInput_table()` to retrieve the input table as above data structure.

- Use `parser.getExpressions()` to retrieve the list of expressions as above data structure.

## Component 2: NFA-GEN

This component is required to construct a
**non-deterministic finite automata (NFA)** for the given regular expressions, combine these
NFAs together with a new starting state to produce one final NFA.

### Background: Finite Automata

These are essentially graphs, like transition diagrams, with a few differences:

- Finite automata are recognizers ; they simply say &*"yes"* or *"no"* about each possible input string.

- Finite automata come in two flavors:

    1. **Nondeterministic nite automata (NFA)** have no restrictions on the labels of their edges. A symbol can label several edges out of the same state, and the empty string (Epsilon), is a possible label.

    2. **Deterministic nite automata (DFA)** have, for each state, and for each symbol of its in

We can represent either an NFA or DFA by a **transition graph**, where the nodes are states and the labeled edges represent the transition function. There is an edge labeled `a` from state `s` to state `t` if and only if `t` is one of the next states for state `s` and input `a`.

<p align='center'><img src="./images/4.png"/></p>

### Implementation Details

We have a `NFAState` class that represents a single node in the NFA. There are two types of these states, it is either:

- An accepting state `NFAAcceptanceState` or,
- Non-accepting state `NFANormalState`.

The accepting state type has an extra attribute to hold the `token_name` it matches.
In general, each `NFAState` has an `id` attribute and a list that contains all the neighbours for this node.
The data structure used for the later is `vector < pair<string , NFAState *>> neighbours`. The pair is to hold both the transition input symbol and a pointer to the next node this node is connected to.

The main class of this component though is  the `NFAGen` class, that is the class responsible for generating the NFAs from each regex and then combining them all into one final NFA or transition graph.

- Use `NFAGen nfa_gen();` to generate a new instance of this class.
- Use `nfa_gen.regex_to_nfa(input_table, regex_list)` to parse both input table and the regex list that is the output of the previous component the language parser
  - They must be of the same data structure type of course.
  - At the end, a pointer to a `NFAState` is retrieved which resembles the root node of the whole final NFA generated from the regex.

This way of implementation will allow us later to introduce and implement **LAG** in a **Pipes and Filters architecture** fashion but we will get back into that part in much detail later on. However, if you are familiar with this architecture already you can quite anticipate what we mean here.
