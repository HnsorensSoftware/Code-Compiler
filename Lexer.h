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
const char* get_token_string(TokenType token) { \
    return words[token]; \
}

// Macro for defining a token
#define DEFINE(token, name) words[TOKEN_ ## token] = name;

// Macro for setting all tokens (run in main)
#define INIT_TOKENS() define_tokens();
