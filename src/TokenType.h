#ifndef TokenType_h
#define TokenType_h
//------------------------------------------------------------------------------

typedef enum TokenTypeTag{
    LINE_COMMENT,
    BLOCK_COMMENT,
    NESTED_COMMENT,
    TODO_COMMENT,

    IDENTIFIER,

    STRING_BYTE,
    ESCAPE_SEQUENCE,

    BIN_PREFIX,
    BIN_LITERAL,

    OCT_PREFIX,
    OCT_LITERAL,

    DEC_LITERAL,

    HEX_PREFIX,
    HEX_LITERAL,

    EXPONENT,

    ERROR_SENTINEL,

    KEYWORD,
    SPECIAL
} TokenType;
//------------------------------------------------------------------------------

const char* token_type_to_string(TokenType type);
//------------------------------------------------------------------------------

#endif
//------------------------------------------------------------------------------
