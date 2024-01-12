# hangman-game

# Coding Style Guide

## File Naming

- Use lowercase letters for file names.
- Separate words with underscores.

    Example: `main.c`, `file_parser.c`

## Function and Variable Naming

- Use camelCase for function names.
- Separate variable names with underscores.
- Be descriptive and use meaningful names.

    Example:
    ```c
    char** word_arrays;
    int calculateScore();
    char *readTextFile();
    ```

## Struct Naming

- Use camelCase for struct names.
- Consider adding a typedef for cleaner usage.

    Example:
    ```c
    typedef struct {
        int size;
        char **lines;
    } TextData;
    ```

## Macro Naming

- Use uppercase letters for macro names.
- Separate words with underscores.

    Example:
    ```c
    #define MAX_WORD_LENGTH 20
    ```

## Constants

- Use uppercase letters for constants.
- Separate words with underscores.

    Example:
    ```c
    const int MAX_ATTEMPTS = 5;
    ```

## Enums

- Use a mixed case for enum names.
- Enumerators are typically uppercase.

    Example:
    ```c
    typedef enum {
        SUCCESS,
        FAILURE,
    } Status;
    ```

## Comments

- Use comments to explain complex code or provide context.
- Follow a consistent commenting style, such as using `//` for single-line comments and `/* */` for multi-line comments.

    Example:
    ```c
    // This function calculates the average score.
    float calculateAverageScore(int scores[], int numScores);
    ```

Remember to update this guide as your coding standards evolve, and encourage your team to adhere to these conventions for a more consistent and maintainable codebase.
