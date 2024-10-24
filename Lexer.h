#include <stdio.h>



// Macro for begining the token declaration stage
#define BEGIN_TOKEN_DECLARATION() \
typedef enum \
{

// Macro for ending the token declaration stage
#define END_TOKEN_DECLARATION() \
} TokenType;

// Macro for declaring a token
#define DECLARE(token) TOKEN_ ## token,

// Macro for begining the token definition stage
#define BEGIN_TOKEN_DEFINITION() \
const char* words[TOKEN_COUNT]; \
void define_tokens() \
{

// Macro for ending the token definition stage
#define END_TOKEN_DEFINITION() \
} \
\
const char* get_token_string(Token token) { \
    if (token.type >= TOKEN_COUNT) return token.value; \
    return words[token.type]; \
}

// Macro for defining a token
#define DEFINE(token, name) words[TOKEN_ ## token] = name;

// Macro for setting all tokens (run in main)
#define INIT_TOKENS() define_tokens();

// Token count for the 'word' array
#define TOKEN_COUNT 15


// Token Declaration
BEGIN_TOKEN_DECLARATION()

// Standard Keywords
DECLARE(INT32)
DECLARE(BOOL)
DECLARE(RETURN)
DECLARE(PLUS)
DECLARE(MINUS)
DECLARE(DIVIDE)
DECLARE(EQUAL)
DECLARE(GREATER)
DECLARE(LESS)
DECLARE(SEMICOLON)
DECLARE(COMMA)
DECLARE(OPEN_PAREN)
DECLARE(CLOSE_PAREN)
DECLARE(OPEN_BRACK)
DECLARE(CLOSE_BRACK)

// Literals (will not be defined)
DECLARE(IDENTIFIER)
DECLARE(NUMBER_LITERAL)
END_TOKEN_DECLARATION()



typedef struct Token
{
    TokenType type;
    char* value;
    int line;
    int column;
} Token;

typedef struct LexerPosition
{
    int position;
    int line;
    int line_begin;
} LexerPosition;

typedef struct TokenBatch
{
    struct Token* tokens;

    int token_count;
    int token_capacity;
} TokenBatch;


void define_tokens();
const char* get_token_string(Token token);
struct LexerPosition create_lexer_position();
Token next_token(const char* source, struct LexerPosition* position);
struct LexerPosition create_lexer_position();
struct TokenBatch create_token_batch();
void add_token(TokenBatch* batch, Token token);
struct TokenBatch parse_tokens(const char* source);
void print_tokens(struct TokenBatch* batch);