// #define DEBUG
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
//------------------------------------------------------------------------------

#include "tree_sitter/parser.h"
#include "debug_macros.h"
//------------------------------------------------------------------------------

#include "TokenType.h"
#include "TokenTree.h"
//------------------------------------------------------------------------------

// These headers contain the "register_*" functions
#include "core.h"
//------------------------------------------------------------------------------

typedef struct ScannerTag{
    int temp;
} Scanner;
//------------------------------------------------------------------------------

#include "TokenType.inc"
#include "TokenTree.inc"
//------------------------------------------------------------------------------

static TokenTree* token_tree     = 0;
static int        instance_count = 0;
//------------------------------------------------------------------------------

void* tree_sitter_alcha_external_scanner_create()
{
    if(!token_tree){
        token_tree = token_tree_new();
        if(!token_tree){
            error("Cannot allocate memory for the token tree");
            return 0;
        }

        debug("Building the token tree...");

        register_core(token_tree);

        debug("Balancing the token tree");
        token_tree_balance(token_tree);
    }
    instance_count++;

    Scanner* scanner = ts_calloc(1, sizeof(Scanner));

    return scanner;
}
//------------------------------------------------------------------------------

void tree_sitter_alcha_external_scanner_destroy(Scanner* scanner)
{
    ts_free(scanner);

    instance_count--;
    if(!instance_count){
        if(token_tree) token_tree_free(token_tree);
        token_tree = 0;
    }
}
//------------------------------------------------------------------------------

unsigned tree_sitter_alcha_external_scanner_serialize(Scanner* scanner, char* buffer)
{
    memcpy(buffer, scanner, sizeof(Scanner));
    return sizeof(Scanner);
}
//------------------------------------------------------------------------------

void tree_sitter_alcha_external_scanner_deserialize(Scanner* scanner, const char* buffer, unsigned length)
{
    memcpy(scanner, buffer, length);
}
//------------------------------------------------------------------------------

static bool whitespace(int32_t character)
{
    return character == ' '  || character == '\t' ||
           character == '\n' || character == '\r';
}
//------------------------------------------------------------------------------

static void skip_whitespace(TSLexer* lexer)
{
    while(whitespace(lexer->lookahead)){
        lexer->advance(lexer, true);
    }
}
//------------------------------------------------------------------------------

// static bool bounded_token(TSLexer* lexer, int32_t bound)
// {
//     while(!lexer->eof(lexer)){
//         if(lexer->lookahead == bound){
//             lexer->advance(lexer, false);
//             lexer->mark_end(lexer);
//             if(lexer->lookahead != bound) return true;
//         }
//         if(lexer->lookahead == '\r') return false;
//         if(lexer->lookahead == '\n') return false;
//         lexer->advance(lexer, false);
//     }
//     return false;
// }
//------------------------------------------------------------------------------

// static bool is_letter_or_digit(int32_t lookahead)
// {
//     return (lookahead >= 'a' && lookahead <= 'z') ||
//            (lookahead >= '0' && lookahead <= '9');
// }
//------------------------------------------------------------------------------

// static bool finish_identifier(TSLexer* lexer, bool expect_letter)
// {
//     int32_t lookahead = lowercase(lexer->lookahead);
//     bool    result = false;
//
//     if(expect_letter){
//         if(!is_letter_or_digit(lookahead)) return false;
//     }
//
//     while(!lexer->eof(lexer)){
//         lexer->mark_end(lexer);
//         if(lookahead == '_') lookahead = advance(lexer);
//         if(!is_letter_or_digit(lookahead)) return result;
//         lookahead = advance(lexer);
//         result = true;
//     }
//     return result;
// }
//------------------------------------------------------------------------------

// static bool is_special_value(int32_t value)
// {
//     switch(value){
//         case 'u':
//         case 'x':
//         case 'z':
//         case 'w':
//         case 'l':
//         case 'h':
//         case '-':
//             return true;
//         default:
//             return false;
//     }
// }
//------------------------------------------------------------------------------

// static bool binary_string_literal(TSLexer* lexer)
// {
//     while(!lexer->eof(lexer)){
//         if(lexer->lookahead == '_') lexer->advance(lexer, false);
//         if((lexer->lookahead < '0' || lexer->lookahead > '1') &&
//            !is_special_value(lowercase(lexer->lookahead))) break;
//         lexer->advance(lexer, false);
//     }
//     if(lexer->lookahead != '"') return false;
//     lexer->advance(lexer, false);
//     lexer->mark_end(lexer);
//     return true;
// }
//------------------------------------------------------------------------------

// static bool octal_string_literal(TSLexer* lexer)
// {
//     while(!lexer->eof(lexer)){
//         if(lexer->lookahead == '_') lexer->advance(lexer, false);
//         if((lexer->lookahead < '0' || lexer->lookahead > '7') &&
//            !is_special_value(lowercase(lexer->lookahead))) break;
//         lexer->advance(lexer, false);
//     }
//     if(lexer->lookahead != '"') return false;
//     lexer->advance(lexer, false);
//     lexer->mark_end(lexer);
//     return true;
// }
//------------------------------------------------------------------------------

// static bool decimal_string_literal(TSLexer* lexer)
// {
//     while(!lexer->eof(lexer)){
//         if(lexer->lookahead == '_') lexer->advance(lexer, false);
//         if((lexer->lookahead < '0' || lexer->lookahead > '9') &&
//            !is_special_value(lowercase(lexer->lookahead))) break;
//         lexer->advance(lexer, false);
//     }
//     if(lexer->lookahead != '"') return false;
//     lexer->advance(lexer, false);
//     lexer->mark_end(lexer);
//     return true;
// }
//------------------------------------------------------------------------------

static void line_comment(TSLexer* lexer)
{
    while(!lexer->eof(lexer)){
        if(lexer->lookahead == '\r') return;
        if(lexer->lookahead == '\n') return;
        lexer->advance(lexer, false);
    }
}
//------------------------------------------------------------------------------

static void block_comment(TSLexer* lexer)
{
    lexer->advance(lexer, false);

    while(!lexer->eof(lexer)){
        if(lexer->lookahead == '*'){
            lexer->advance(lexer, false);
            if(lexer->lookahead == '/'){
                lexer->advance(lexer, false);
                return;
            }
        }else{
            lexer->advance(lexer, false);
        }
    }
}
//------------------------------------------------------------------------------

static void nested_comment(TSLexer* lexer)
{
    lexer->advance(lexer, false);

    while(!lexer->eof(lexer)){
        if(lexer->lookahead == '+'){
            lexer->advance(lexer, false);
            if(lexer->lookahead == '/'){
                lexer->advance(lexer, false);
                return;
            }
        }else if(lexer->lookahead == '/'){
            lexer->advance(lexer, false);
            if(lexer->lookahead == '+') nested_comment(lexer);
        }else{
            lexer->advance(lexer, false);
        }
    }
}
//------------------------------------------------------------------------------

static void bin_literal(TSLexer* lexer)
{
    while(!lexer->eof(lexer)){
        if((lexer->lookahead < '0' || lexer->lookahead > '1') &&
           lexer->lookahead != '_' &&
           lexer->lookahead != '.' ) return;
        lexer->advance(lexer, false);
    }
}
//------------------------------------------------------------------------------

static void oct_literal(TSLexer* lexer)
{
    while(!lexer->eof(lexer)){
        if((lexer->lookahead < '0' || lexer->lookahead > '7') &&
           lexer->lookahead != '_' &&
           lexer->lookahead != '.' ) return;
        lexer->advance(lexer, false);
    }
}
//------------------------------------------------------------------------------

static void dec_literal(TSLexer* lexer)
{
    while(!lexer->eof(lexer)){
        if((lexer->lookahead < '0' || lexer->lookahead > '9') &&
           lexer->lookahead != '_' &&
           lexer->lookahead != '.' ) return;
        lexer->advance(lexer, false);
    }
}
//------------------------------------------------------------------------------

static bool hex_digit(int32_t character)
{
    return (character >= '0' && character <= '9') ||
           (character >= 'a' && character <= 'f') ||
           (character >= 'A' && character <= 'F');
}
//------------------------------------------------------------------------------

static void hex_literal(TSLexer* lexer)
{
    while(!lexer->eof(lexer)){
        if(!hex_digit(lexer->lookahead) &&
           lexer->lookahead != '_' &&
           lexer->lookahead != '.' ) return;
        lexer->advance(lexer, false);
    }
}
//------------------------------------------------------------------------------

static void oct_char(TSLexer* lexer)
{
    while(!lexer->eof(lexer)){
        if(lexer->lookahead < '0' || lexer->lookahead > '7') return;
        lexer->advance(lexer, false);
    }
}
//------------------------------------------------------------------------------

static void hex_char(TSLexer* lexer, int length)
{
    lexer->advance(lexer, false);

    while(!lexer->eof(lexer)){
        if(!hex_digit(lexer->lookahead)) return;
        lexer->advance(lexer, false);
        length--;
        if(length == 0) return;
    }
}
//------------------------------------------------------------------------------

static void html_name(TSLexer* lexer)
{
    lexer->advance(lexer, false);

    while(!lexer->eof(lexer)){
        if((lexer->lookahead < 'a' || lexer->lookahead > 'z') &&
           (lexer->lookahead < 'A' || lexer->lookahead > 'Z')) break;
        lexer->advance(lexer, false);
    }
    if(lexer->lookahead == ';') lexer->advance(lexer, false);
}
//------------------------------------------------------------------------------

static void escape_sequence(TSLexer* lexer)
{
    lexer->advance(lexer, false);

    switch(lexer->lookahead){
        case 'x':
            hex_char(lexer, 2);
            break;
        case 'u':
            hex_char(lexer, 4);
            break;
        case 'U':
            hex_char(lexer, 8);
            break;
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
            oct_char(lexer);
            break;
        case '&':
            html_name(lexer);
            break;
        default:
            lexer->advance(lexer, false);
            break;
    }
}
//------------------------------------------------------------------------------

static void exponent(TSLexer* lexer)
{
    lexer->advance(lexer, false);

    if(lexer->lookahead == '-' || lexer->lookahead == '+')
        lexer->advance(lexer, false);

    while(!lexer->eof(lexer)){
        if(lexer->lookahead < '0' || lexer->lookahead > '9') return;
        lexer->advance(lexer, false);
    }
}
//------------------------------------------------------------------------------

#define RETURN(type) do{                                                               \
    lexer->result_symbol = type;                                                       \
    debug("Returning %s", valid_symbols[type] ? token_type_to_string(type) : "false"); \
    return valid_symbols[type];                                                        \
}while(0);

#define RETURN_FALSE do{          \
    debug("Returning false..."); \
    return false;                \
}while(0);
//------------------------------------------------------------------------------

bool tree_sitter_alcha_external_scanner_scan(Scanner* scanner, TSLexer* lexer, const bool* valid_symbols)
{
    if(lexer->eof(lexer)) RETURN_FALSE;

    #ifdef DEBUG
        if(valid_symbols[ERROR_SENTINEL]){
            debug("Error correction mode");
        }else{
            debug("Looking for:");
            for(int n = 0; n < ERROR_SENTINEL; n++){
                if(valid_symbols[n]) printf("    %s\n", token_type_to_string(n));
            }
            printf("\n");
        }
    #endif

    if((valid_symbols[STRING_BYTE] || valid_symbols[ESCAPE_SEQUENCE]) && !valid_symbols[ERROR_SENTINEL]){
        switch(lexer->lookahead){
            case '"':
                RETURN_FALSE;
            case '\\':
                escape_sequence(lexer);
                RETURN(ESCAPE_SEQUENCE);
            default:
                lexer->advance(lexer, false);
                RETURN(STRING_BYTE);
        }
    }

    if(valid_symbols[EXPONENT] && !valid_symbols[ERROR_SENTINEL]){
        switch(lexer->lookahead){
            case 'e': case 'p':
            case 'E': case 'P':
                exponent(lexer);
                RETURN(EXPONENT);
            default:
                break;
        }
    }

    if(!valid_symbols[BIN_LITERAL] &&
       !valid_symbols[OCT_LITERAL] &&
       !valid_symbols[HEX_LITERAL]) skip_whitespace(lexer);

    if(lexer->eof(lexer)) RETURN_FALSE;

    switch(lexer->lookahead){
        case '/':
            lexer->advance(lexer, false);
            switch(lexer->lookahead){
                case '/':
                    line_comment(lexer);
                    RETURN(LINE_COMMENT);
                case '*':
                    block_comment(lexer);
                    RETURN(BLOCK_COMMENT);
                case '+':
                    nested_comment(lexer);
                    RETURN(NESTED_COMMENT);
                default:
                    RETURN_FALSE;
            }

        case '!':
            lexer->advance(lexer, false);
            if(lexer->lookahead == '!'){
                if(valid_symbols[TODO_COMMENT]){
                    line_comment(lexer);
                    RETURN(TODO_COMMENT);
                }else{
                    RETURN_FALSE;
                }
            }else{
                RETURN_FALSE;
            }

        case '0':
            lexer->advance(lexer, false);
            switch(lexer->lookahead){
                case 'b':
                    lexer->advance(lexer, false);
                    RETURN(BIN_PREFIX);
                case 'o':
                    lexer->advance(lexer, false);
                    RETURN(OCT_PREFIX);
                case 'x':
                    lexer->advance(lexer, false);
                    RETURN(HEX_PREFIX);
                default:
                    dec_literal(lexer);
                    RETURN(DEC_LITERAL);
            }

        case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            if(valid_symbols[BIN_LITERAL]){
                bin_literal(lexer);
                RETURN(BIN_LITERAL);
            }else if(valid_symbols[OCT_LITERAL]){
                oct_literal(lexer);
                RETURN(OCT_LITERAL);
            }else if(valid_symbols[DEC_LITERAL]){
                dec_literal(lexer);
                RETURN(DEC_LITERAL);
            }else if(valid_symbols[HEX_LITERAL]){
                hex_literal(lexer);
                RETURN(HEX_LITERAL);
            }else{
                RETURN_FALSE;
            }

        default:
            if(valid_symbols[HEX_LITERAL] && hex_digit(lexer->lookahead)){
                hex_literal(lexer);
                RETURN(HEX_LITERAL);

            }else if(valid_symbols[IDENTIFIER]){
                // TODO
            }
            RETURN_FALSE;
    }

    RETURN_FALSE;
}
//------------------------------------------------------------------------------

