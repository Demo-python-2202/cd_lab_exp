#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 100

const char *keywords[] = {"int", "float", "if", "else", "return", "while", "for", "char", "double", "void", "main"};
const char delimiters[] = "(){};";
const char operators[] = "+-*/<>=!&|";

// Check if the word is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        if (strcmp(word, keywords[i]) == 0) return 1;
    return 0;
}

// Check if the character is an operator
int isOperator(char ch) {
    return strchr(operators, ch) != NULL;
}

// Check if the character is a delimiter
int isDelimiter(char ch) {
    return strchr(delimiters, ch) != NULL;
}

// Check if the string is a number (integer or float)
int isNumber(char *str) {
    int dotCount = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') dotCount++;
        else if (!isdigit(str[i])) return 0;
    }
    return dotCount <= 1;  // Allow at most one dot for float
}

int main() {
    char input[MAX_LEN], word[MAX_LEN];
    printf("Enter the string: ");
    fgets(input, MAX_LEN, stdin); // Read input string

    int i = 0, j = 0;
    char delimitersFound[MAX_LEN] = "", operatorsFound[MAX_LEN] = "";
    char identifiers[MAX_LEN][MAX_LEN], keywordsFound[MAX_LEN][MAX_LEN],
         literals[MAX_LEN][MAX_LEN], constants[MAX_LEN][MAX_LEN];

    int idCount = 0, kwCount = 0, litCount = 0, constCount = 0;

    // Loop through each character of the input
    while (input[i] != '\0') {
        char ch = input[i];

        // Handle literals (strings enclosed in quotes)
        if (ch == '\"') {
            j = 0;
            i++; // Skip the opening quote
            while (input[i] != '\"' && input[i] != '\0')
                word[j++] = input[i++];
            word[j] = '\0';
            if (input[i] == '\"') i++; // Skip the closing quote
            strcpy(literals[litCount++], word);
        }
        // Handle operators
        else if (isOperator(ch)) {
            strncat(operatorsFound, &ch, 1);
        }
        // Handle delimiters
        else if (isDelimiter(ch)) {
            strncat(delimitersFound, &ch, 1);
        }
        // Handle identifiers and constants
        else if (isalnum(ch) || ch == '.') {
            j = 0;
            while (isalnum(input[i]) || input[i] == '.')
                word[j++] = input[i++];
            word[j] = '\0';
            i--;  // Step back as the loop will increment i

            if (isKeyword(word))
                strcpy(keywordsFound[kwCount++], word);
            else if (isNumber(word))
                strcpy(constants[constCount++], word);
            else
                strcpy(identifiers[idCount++], word);
        }
        i++; // Move to next character
    }

    // Output results
    printf("\nDelimiters: %s\nOperators: %s\nIdentifiers: ", delimitersFound, operatorsFound);
    for (int k = 0; k < idCount; k++)
        printf("%s ", identifiers[k]);

    printf("\nKeywords: ");
    for (int k = 0; k < kwCount; k++)
        printf("%s ", keywordsFound[k]);

    printf("\nConstants: ");
    for (int k = 0; k < constCount; k++)
        printf("%s ", constants[k]);

    printf("\nLiterals: ");
    for (int k = 0; k < litCount; k++)
        printf("\"%s\" ", literals[k]);

    return 0;
}

// int x = 10 + 5 * (2 - 3); if (x > 0) return x;
