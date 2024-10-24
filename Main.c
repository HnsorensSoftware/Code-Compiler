#include "Lexer.h"


int main()
{
    INIT_TOKENS()

    const char* source = "int32 main();";

    struct TokenBatch batch = parse_tokens(source);
    print_tokens(&batch);

    return 0;
}