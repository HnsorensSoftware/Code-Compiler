#include "Lexer.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Token Definitions
BEGIN_TOKEN_DEFINITION()

// Defined Keywords
DEFINE(INT32, "int32")
DEFINE(BOOL, "bool")
DEFINE(RETURN, "return")
DEFINE(PLUS, "+")
DEFINE(MINUS, "-")
DEFINE(DIVIDE, "/")
DEFINE(EQUAL, "=")
DEFINE(GREATER, ">")
DEFINE(LESS, "<")
DEFINE(SEMICOLON, ";")
DEFINE(COMMA, ",")
DEFINE(OPEN_PAREN, "(")
DEFINE(CLOSE_PAREN, ")")
DEFINE(OPEN_BRACK, "{")
DEFINE(CLOSE_BRACK, "}")

END_TOKEN_DEFINITION()

// Enum for word type (for literals)
typedef enum WordType
{
    WORD_DIGITS,
    WORD_ALNUM,
    WORD_PUNC,
    WORD_NONE
} WordType;

// Function Declaration
#define POSITION(offset) position->position+offset
#define INC_POSITION(increment) position->position+=increment

// Function Definition
struct Token next_token(const char* source, struct LexerPosition* position)
{

    // gets the current character
    char start_char = source[POSITION(0)];

    // Ignores all spaces
    while (start_char == ' ' || start_char == '\t' || start_char == '\n')
    {
        // when encountering a new line, change the line
        if (start_char == '\n')
        {
            position->line ++;
            position->lineBegin = POSITION(1);
        }
        
        // increment to the next character
        INC_POSITION(1);
        start_char = source[POSITION(0)];
    }

    int current_column = position->position - position->lineBegin;

    /* ******************** Create Word ********************* */


    char word[256];
    WordType word_type = WORD_NONE; // Used to identify literal type

    int word_index = 0; // Used to know which character is being checked, also defines the length of the word

    // Populates the word
    if (isdigit(start_char))
    {
        while (isdigit(source[POSITION(0)]))
        {
            printf("%c\n", source[POSITION(0)]);
            word[word_index] = source[POSITION(0)];
            word_index++;
            INC_POSITION(1);
        }
        word_type = WORD_DIGITS;
        word[word_index] = '\0';
    }
    else if (isalpha(start_char))
    {
        while (isalnum(source[POSITION(0)]))
        {
            word[word_index] = source[POSITION(0)];
            word_index++;
            INC_POSITION(1);
        }
        word_type = WORD_ALNUM;
        word[word_index] = '\0';
    }
    else if (ispunct(start_char)) // puncuations are limited to a length of 1
    {
        word[word_index] = start_char;
        word_index++;
        INC_POSITION(1);
        word_type = WORD_PUNC;
        word[word_index] = '\0';
    }
    else
    {
        printf("Unrecognized character");
    }

    /* ******************** Find Token ********************* */

    // Attempts to match the word with an existing token
    struct Token token;
    int type_set = 0;
    for (int i = 0; i < TOKEN_COUNT; i++)
    {
        if (strcmp(words[i], word) == 0)
        {
            token.type = i;
            type_set = 1;
            break;
        }
    }

    // Attempts to create a literal or identifier if no keyword is found
    if (!type_set)
    {
        // Chooses the type of literal
        switch (word_type)
        {
            case WORD_DIGITS:
                token.type = TOKEN_NUMBER_LITERAL;
                token.value = (char*)malloc(word_index);
                memcpy(token.value, word, word_index);
                break;
            case WORD_ALNUM:
                token.type = TOKEN_IDENTIFIER;
                token.value = (char*)malloc(word_index);
                memcpy(token.value, word, word_index);
                break;
            case WORD_PUNC:
            // There should be no literals containing operators
                printf("Unrecognized Operator!");
                break;
            default:
                printf("Unrecognized Text!");

        }
    }

    // Sets the column and line number for later debugging.
    token.column = current_column;
    token.line = position->line;

    return token;
}


struct LexerPosition create_lexer_position()
{
    LexerPosition position;
    position.position = 0;
    position.line = 0;
    position.lineBegin = 0;

    return position;
}