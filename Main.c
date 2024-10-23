#include "Lexer.h"


int main()
{
    INIT_TOKENS()

    const char* source = "int32 main();";


    struct LexerPosition position = create_lexer_position();

    struct Token token1 = next_token(source, &position);
    struct Token token2 = next_token(source, &position);
    struct Token token3 = next_token(source, &position);
    struct Token token4 = next_token(source, &position);
    struct Token token5 = next_token(source, &position);

    printf("Token1: %s, Token2: %s, Token3: %s, Token4: %s, Token5: %s \n", get_token_string(token1), get_token_string(token2), get_token_string(token3), get_token_string(token4), get_token_string(token5));

    return 0;
}