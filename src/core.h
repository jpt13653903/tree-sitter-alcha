#ifndef core_h
#define core_h
//------------------------------------------------------------------------------

#include "TokenType.h"
//------------------------------------------------------------------------------

static void register_keywords(TokenTree* token_tree)
{
    token_tree_insert(token_tree, "void",      KEYWORD);
    token_tree_insert(token_tree, "auto",      KEYWORD);

    token_tree_insert(token_tree, "pin",       KEYWORD);
    token_tree_insert(token_tree, "net",       KEYWORD);

    token_tree_insert(token_tree, "byte",      KEYWORD);
    token_tree_insert(token_tree, "char",      KEYWORD);
    token_tree_insert(token_tree, "num",       KEYWORD);

    token_tree_insert(token_tree, "true",      KEYWORD);
    token_tree_insert(token_tree, "false",     KEYWORD);

    token_tree_insert(token_tree, "class",     KEYWORD);
    token_tree_insert(token_tree, "enum",      KEYWORD);
    token_tree_insert(token_tree, "struct",    KEYWORD);
    token_tree_insert(token_tree, "group",     KEYWORD);
    token_tree_insert(token_tree, "alias",     KEYWORD);

    token_tree_insert(token_tree, "input",     KEYWORD);
    token_tree_insert(token_tree, "output",    KEYWORD);

    token_tree_insert(token_tree, "public",    KEYWORD);
    token_tree_insert(token_tree, "private",   KEYWORD);
    token_tree_insert(token_tree, "protected", KEYWORD);

    token_tree_insert(token_tree, "if",        KEYWORD);
    token_tree_insert(token_tree, "else",      KEYWORD);
    token_tree_insert(token_tree, "for",       KEYWORD);
    token_tree_insert(token_tree, "in",        KEYWORD);
    token_tree_insert(token_tree, "while",     KEYWORD);
    token_tree_insert(token_tree, "loop",      KEYWORD);

    token_tree_insert(token_tree, "switch",    KEYWORD);
    token_tree_insert(token_tree, "case",      KEYWORD);
    token_tree_insert(token_tree, "default",   KEYWORD);

    token_tree_insert(token_tree, "import",    KEYWORD);
    token_tree_insert(token_tree, "as",        KEYWORD);

    token_tree_insert(token_tree, "return",    KEYWORD);
    token_tree_insert(token_tree, "break",     KEYWORD);
    token_tree_insert(token_tree, "continue",  KEYWORD);
    token_tree_insert(token_tree, "goto",      KEYWORD);

    token_tree_insert(token_tree, "func",      KEYWORD);
    token_tree_insert(token_tree, "inline",    KEYWORD);

    token_tree_insert(token_tree, "rtl",       KEYWORD);
    token_tree_insert(token_tree, "fsm",       KEYWORD);
    token_tree_insert(token_tree, "hdl",       KEYWORD);

    token_tree_insert(token_tree, "stimulus",  KEYWORD);
    token_tree_insert(token_tree, "emulate",   KEYWORD);
    token_tree_insert(token_tree, "sequence",  KEYWORD);
    token_tree_insert(token_tree, "assert",    KEYWORD);
    token_tree_insert(token_tree, "wait",      KEYWORD);

    token_tree_insert(token_tree, "posedge",   KEYWORD);
    token_tree_insert(token_tree, "negedge",   KEYWORD);
}
//------------------------------------------------------------------------------

static void register_constants(TokenTree* token_tree)
{
    token_tree_insert(token_tree, "pi",          BUILTIN_CONST);
    token_tree_insert(token_tree, "e",           BUILTIN_CONST);
    token_tree_insert(token_tree, "i",           BUILTIN_CONST);
    token_tree_insert(token_tree, "j",           BUILTIN_CONST);
    token_tree_insert(token_tree, "__YEAR__",    BUILTIN_CONST);
    token_tree_insert(token_tree, "__MONTH__",   BUILTIN_CONST);
    token_tree_insert(token_tree, "__DAY__",     BUILTIN_CONST);
    token_tree_insert(token_tree, "__HOUR__",    BUILTIN_CONST);
    token_tree_insert(token_tree, "__MINUTE__",  BUILTIN_CONST);
    token_tree_insert(token_tree, "__SECOND__",  BUILTIN_CONST);
    token_tree_insert(token_tree, "__WEEKDAY__", BUILTIN_CONST);
    token_tree_insert(token_tree, "__YEARDAY__", BUILTIN_CONST);
}
//------------------------------------------------------------------------------

static void register_specials(TokenTree* token_tree)
{
    token_tree_insert(token_tree, "__FILE__",      BUILTIN_CONST);
    token_tree_insert(token_tree, "__LINE__",      BUILTIN_CONST);
    token_tree_insert(token_tree, "__DATE__",      BUILTIN_CONST);
    token_tree_insert(token_tree, "__TIME__",      BUILTIN_CONST);
    token_tree_insert(token_tree, "__CLASS__",     BUILTIN_CONST);
    token_tree_insert(token_tree, "__FUNCTION__",  BUILTIN_CONST);
    token_tree_insert(token_tree, "__NAMESPACE__", BUILTIN_CONST);
}
//------------------------------------------------------------------------------

static void register_functions(TokenTree* token_tree)
{
    token_tree_insert(token_tree, "print",  BUILTIN_FUNC);
    token_tree_insert(token_tree, "rose",   BUILTIN_FUNC);
    token_tree_insert(token_tree, "fell",   BUILTIN_FUNC);
    token_tree_insert(token_tree, "stable", BUILTIN_FUNC);
    token_tree_insert(token_tree, "past",   BUILTIN_FUNC);
}
//------------------------------------------------------------------------------

void register_core(TokenTree* token_tree)
{
    register_keywords (token_tree);
    register_constants(token_tree);
    register_specials (token_tree);
    register_functions(token_tree);
}
//------------------------------------------------------------------------------

#endif
//------------------------------------------------------------------------------

