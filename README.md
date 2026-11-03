C to HTML Converter – Syntax Highlighter

Overview

C to HTML Converter is a command-line application developed in C that converts C source code into an HTML file with syntax highlighting.

The program reads a `.c` source file, identifies different C language elements, and wraps them in HTML `<span>` tags with CSS classes. The generated HTML file uses an external CSS stylesheet to display the highlighted source code in a web browser.

Features

- Keyword Detection: Identifies C keywords such as `int`, `return`, `if`, `while`, and `struct`.
- Identifier Detection: Recognizes variable and function identifiers.
- Comment Highlighting: Identifies single-line (`//`) and multi-line (`/* */`) comments.
- Preprocessor Detection: Identifies preprocessor directives.
- Header File Detection: Recognizes included header files.
- Operator Detection: Identifies arithmetic, assignment, and relational operators.
- Symbol Detection: Recognizes brackets, braces, parentheses, commas, and other symbols.
- Numeric Constant Detection: Identifies integer and floating-point constants.
- String Detection: Identifies string literals.
- HTML Generation: Generates an HTML document with syntax-highlighted C source code.
- CSS Styling: Uses an external stylesheet to apply different colors to recognized language elements.
- Terminal Feedback: Displays conversion status and output information with formatted messages and emojis.

Concepts Applied

- File handling in C (`FILE`, `fopen()`, `fgetc()`, `fprintf()`, `fclose()`)
- Command-line arguments (`argc`, `argv`)
- String manipulation (`strcmp()`, `strstr()`, `strcat()`)
- Character handling (`isalpha()`, `isdigit()`, `isspace()`, `isalnum()`)
- User-defined functions
- Header files and modular programming
- Conditional statements and loops
- HTML tags and CSS styling
- Basic lexical analysis concepts

Project Structure

```text
SOURCE_TO_HTML_C/
│
├── main.c
├── source_to_html.c
├── html_head_foot.c
├── header.h
├── style.css
├── README.md
└── .gitignore
```

How It Works

1. Accepts a C source file path through command-line arguments.
2. Opens the input source file in read mode.
3. Creates an output HTML file named `output.html`.
4. Reads the source file character by character.
5. Identifies C language elements using custom functions and character/string operations.
6. Wraps recognized elements with corresponding HTML `<span>` tags and CSS classes.
7. Adds the HTML document structure using separate initialization and ending functions.
8. Applies syntax highlighting through the external `style.css` file.
9. Generates the final HTML document, which can be opened in a web browser.

Compilation and Execution

Compile the project using GCC:

```bash
gcc main.c source_to_html.c html_head_foot.c -o source_to_html
```

Run the executable by passing the C source file as a command-line argument:

```bash
./source_to_html input.c
```

On Windows:

```bash
gcc main.c source_to_html.c html_head_foot.c -o source_to_html.exe
source_to_html.exe input.c
```

Replace `input.c` with the path to your C source file.

The generated HTML file will be:

```text
output.html
```

Keep `style.css` in the same directory as `output.html` so the browser can load the stylesheet correctly.

Output

The generated HTML file displays the input C source code with different colors for recognized language elements, including:

- Keywords
- Identifiers
- Comments
- Preprocessor directives
- Header files
- Operators
- Symbols
- Numeric constants
- String literals

Future Improvements

- Improve handling of nested and complex expressions.
- Support additional C operators and language constructs.
- Improve handling of character literals and escaped characters.
- Add robust handling for longer tokens and comments.
- Improve parsing accuracy using a more structured lexical analysis approach.
- Support additional programming languages.

Author

Developed as a C programming project to explore file handling, string processing, lexical analysis concepts, modular programming, and HTML generation.
