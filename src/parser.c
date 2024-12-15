#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 20
#define LARGE_STATE_COUNT 6
#define SYMBOL_COUNT 25
#define ALIAS_COUNT 0
#define TOKEN_COUNT 20
#define EXTERNAL_TOKEN_COUNT 16
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_i = 1,
  anon_sym_j = 2,
  anon_sym_DQUOTE = 3,
  sym_line_comment = 4,
  sym_block_comment = 5,
  sym_nested_comment = 6,
  sym_todo_comment = 7,
  sym_identifier = 8,
  sym__string_byte = 9,
  sym_escape_sequence = 10,
  sym_bin_prefix = 11,
  sym_bin_literal = 12,
  sym_oct_prefix = 13,
  sym_oct_literal = 14,
  sym_dec_literal = 15,
  sym_hex_prefix = 16,
  sym_hex_literal = 17,
  sym_exponent = 18,
  sym_error_sentinel = 19,
  sym_design_file = 20,
  sym_literal = 21,
  sym_string = 22,
  aux_sym_design_file_repeat1 = 23,
  aux_sym_string_repeat1 = 24,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_i] = "i",
  [anon_sym_j] = "j",
  [anon_sym_DQUOTE] = "\"",
  [sym_line_comment] = "line_comment",
  [sym_block_comment] = "block_comment",
  [sym_nested_comment] = "nested_comment",
  [sym_todo_comment] = "todo_comment",
  [sym_identifier] = "identifier",
  [sym__string_byte] = "_string_byte",
  [sym_escape_sequence] = "escape_sequence",
  [sym_bin_prefix] = "bin_prefix",
  [sym_bin_literal] = "bin_literal",
  [sym_oct_prefix] = "oct_prefix",
  [sym_oct_literal] = "oct_literal",
  [sym_dec_literal] = "dec_literal",
  [sym_hex_prefix] = "hex_prefix",
  [sym_hex_literal] = "hex_literal",
  [sym_exponent] = "exponent",
  [sym_error_sentinel] = "error_sentinel",
  [sym_design_file] = "design_file",
  [sym_literal] = "literal",
  [sym_string] = "string",
  [aux_sym_design_file_repeat1] = "design_file_repeat1",
  [aux_sym_string_repeat1] = "string_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_i] = anon_sym_i,
  [anon_sym_j] = anon_sym_j,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [sym_line_comment] = sym_line_comment,
  [sym_block_comment] = sym_block_comment,
  [sym_nested_comment] = sym_nested_comment,
  [sym_todo_comment] = sym_todo_comment,
  [sym_identifier] = sym_identifier,
  [sym__string_byte] = sym__string_byte,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_bin_prefix] = sym_bin_prefix,
  [sym_bin_literal] = sym_bin_literal,
  [sym_oct_prefix] = sym_oct_prefix,
  [sym_oct_literal] = sym_oct_literal,
  [sym_dec_literal] = sym_dec_literal,
  [sym_hex_prefix] = sym_hex_prefix,
  [sym_hex_literal] = sym_hex_literal,
  [sym_exponent] = sym_exponent,
  [sym_error_sentinel] = sym_error_sentinel,
  [sym_design_file] = sym_design_file,
  [sym_literal] = sym_literal,
  [sym_string] = sym_string,
  [aux_sym_design_file_repeat1] = aux_sym_design_file_repeat1,
  [aux_sym_string_repeat1] = aux_sym_string_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_i] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_j] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [sym_line_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_block_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_nested_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_todo_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym__string_byte] = {
    .visible = false,
    .named = true,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym_bin_prefix] = {
    .visible = true,
    .named = true,
  },
  [sym_bin_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_oct_prefix] = {
    .visible = true,
    .named = true,
  },
  [sym_oct_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_dec_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_hex_prefix] = {
    .visible = true,
    .named = true,
  },
  [sym_hex_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_exponent] = {
    .visible = true,
    .named = true,
  },
  [sym_error_sentinel] = {
    .visible = true,
    .named = true,
  },
  [sym_design_file] = {
    .visible = true,
    .named = true,
  },
  [sym_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_design_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(2);
      if (lookahead == '"') ADVANCE(5);
      if (lookahead == 'i') ADVANCE(3);
      if (lookahead == 'j') ADVANCE(4);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1);
      END_STATE();
    case 1:
      if (eof) ADVANCE(2);
      if (lookahead == '"') ADVANCE(5);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1);
      END_STATE();
    case 2:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 3:
      ACCEPT_TOKEN(anon_sym_i);
      END_STATE();
    case 4:
      ACCEPT_TOKEN(anon_sym_j);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 0, .external_lex_state = 2},
  [2] = {.lex_state = 0, .external_lex_state = 3},
  [3] = {.lex_state = 0, .external_lex_state = 2},
  [4] = {.lex_state = 0, .external_lex_state = 3},
  [5] = {.lex_state = 0, .external_lex_state = 2},
  [6] = {.lex_state = 0, .external_lex_state = 2},
  [7] = {.lex_state = 0, .external_lex_state = 2},
  [8] = {.lex_state = 0, .external_lex_state = 2},
  [9] = {.lex_state = 0, .external_lex_state = 2},
  [10] = {.lex_state = 0, .external_lex_state = 2},
  [11] = {.lex_state = 0, .external_lex_state = 2},
  [12] = {.lex_state = 0, .external_lex_state = 2},
  [13] = {.lex_state = 0, .external_lex_state = 4},
  [14] = {.lex_state = 0, .external_lex_state = 4},
  [15] = {.lex_state = 0, .external_lex_state = 4},
  [16] = {.lex_state = 0, .external_lex_state = 5},
  [17] = {.lex_state = 0, .external_lex_state = 6},
  [18] = {.lex_state = 0, .external_lex_state = 7},
  [19] = {.lex_state = 0, .external_lex_state = 8},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_i] = ACTIONS(1),
    [anon_sym_j] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_line_comment] = ACTIONS(3),
    [sym_block_comment] = ACTIONS(3),
    [sym_nested_comment] = ACTIONS(3),
    [sym_todo_comment] = ACTIONS(3),
    [sym_identifier] = ACTIONS(1),
    [sym__string_byte] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [sym_bin_prefix] = ACTIONS(1),
    [sym_bin_literal] = ACTIONS(1),
    [sym_oct_prefix] = ACTIONS(1),
    [sym_oct_literal] = ACTIONS(1),
    [sym_dec_literal] = ACTIONS(1),
    [sym_hex_prefix] = ACTIONS(1),
    [sym_hex_literal] = ACTIONS(1),
    [sym_exponent] = ACTIONS(1),
    [sym_error_sentinel] = ACTIONS(1),
  },
  [1] = {
    [sym_design_file] = STATE(19),
    [sym_literal] = STATE(3),
    [sym_string] = STATE(3),
    [aux_sym_design_file_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_DQUOTE] = ACTIONS(7),
    [sym_line_comment] = ACTIONS(3),
    [sym_block_comment] = ACTIONS(3),
    [sym_nested_comment] = ACTIONS(3),
    [sym_todo_comment] = ACTIONS(3),
    [sym_bin_prefix] = ACTIONS(9),
    [sym_oct_prefix] = ACTIONS(11),
    [sym_dec_literal] = ACTIONS(13),
    [sym_hex_prefix] = ACTIONS(15),
  },
  [2] = {
    [ts_builtin_sym_end] = ACTIONS(17),
    [anon_sym_i] = ACTIONS(19),
    [anon_sym_j] = ACTIONS(19),
    [anon_sym_DQUOTE] = ACTIONS(17),
    [sym_line_comment] = ACTIONS(3),
    [sym_block_comment] = ACTIONS(3),
    [sym_nested_comment] = ACTIONS(3),
    [sym_todo_comment] = ACTIONS(3),
    [sym_bin_prefix] = ACTIONS(17),
    [sym_oct_prefix] = ACTIONS(17),
    [sym_dec_literal] = ACTIONS(17),
    [sym_hex_prefix] = ACTIONS(17),
    [sym_exponent] = ACTIONS(21),
  },
  [3] = {
    [sym_literal] = STATE(5),
    [sym_string] = STATE(5),
    [aux_sym_design_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(23),
    [anon_sym_DQUOTE] = ACTIONS(7),
    [sym_line_comment] = ACTIONS(3),
    [sym_block_comment] = ACTIONS(3),
    [sym_nested_comment] = ACTIONS(3),
    [sym_todo_comment] = ACTIONS(3),
    [sym_bin_prefix] = ACTIONS(9),
    [sym_oct_prefix] = ACTIONS(11),
    [sym_dec_literal] = ACTIONS(13),
    [sym_hex_prefix] = ACTIONS(15),
  },
  [4] = {
    [ts_builtin_sym_end] = ACTIONS(25),
    [anon_sym_i] = ACTIONS(27),
    [anon_sym_j] = ACTIONS(27),
    [anon_sym_DQUOTE] = ACTIONS(25),
    [sym_line_comment] = ACTIONS(3),
    [sym_block_comment] = ACTIONS(3),
    [sym_nested_comment] = ACTIONS(3),
    [sym_todo_comment] = ACTIONS(3),
    [sym_bin_prefix] = ACTIONS(25),
    [sym_oct_prefix] = ACTIONS(25),
    [sym_dec_literal] = ACTIONS(25),
    [sym_hex_prefix] = ACTIONS(25),
    [sym_exponent] = ACTIONS(29),
  },
  [5] = {
    [sym_literal] = STATE(5),
    [sym_string] = STATE(5),
    [aux_sym_design_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(31),
    [anon_sym_DQUOTE] = ACTIONS(33),
    [sym_line_comment] = ACTIONS(3),
    [sym_block_comment] = ACTIONS(3),
    [sym_nested_comment] = ACTIONS(3),
    [sym_todo_comment] = ACTIONS(3),
    [sym_bin_prefix] = ACTIONS(36),
    [sym_oct_prefix] = ACTIONS(39),
    [sym_dec_literal] = ACTIONS(42),
    [sym_hex_prefix] = ACTIONS(45),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 3,
    ACTIONS(27), 2,
      anon_sym_i,
      anon_sym_j,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
    ACTIONS(25), 6,
      sym_bin_prefix,
      sym_oct_prefix,
      sym_dec_literal,
      sym_hex_prefix,
      ts_builtin_sym_end,
      anon_sym_DQUOTE,
  [19] = 3,
    ACTIONS(50), 2,
      anon_sym_i,
      anon_sym_j,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
    ACTIONS(48), 6,
      sym_bin_prefix,
      sym_oct_prefix,
      sym_dec_literal,
      sym_hex_prefix,
      ts_builtin_sym_end,
      anon_sym_DQUOTE,
  [38] = 2,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
    ACTIONS(25), 6,
      sym_bin_prefix,
      sym_oct_prefix,
      sym_dec_literal,
      sym_hex_prefix,
      ts_builtin_sym_end,
      anon_sym_DQUOTE,
  [53] = 2,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
    ACTIONS(52), 6,
      sym_bin_prefix,
      sym_oct_prefix,
      sym_dec_literal,
      sym_hex_prefix,
      ts_builtin_sym_end,
      anon_sym_DQUOTE,
  [68] = 2,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
    ACTIONS(48), 6,
      sym_bin_prefix,
      sym_oct_prefix,
      sym_dec_literal,
      sym_hex_prefix,
      ts_builtin_sym_end,
      anon_sym_DQUOTE,
  [83] = 2,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
    ACTIONS(54), 6,
      sym_bin_prefix,
      sym_oct_prefix,
      sym_dec_literal,
      sym_hex_prefix,
      ts_builtin_sym_end,
      anon_sym_DQUOTE,
  [98] = 2,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
    ACTIONS(56), 6,
      sym_bin_prefix,
      sym_oct_prefix,
      sym_dec_literal,
      sym_hex_prefix,
      ts_builtin_sym_end,
      anon_sym_DQUOTE,
  [113] = 4,
    ACTIONS(58), 1,
      anon_sym_DQUOTE,
    STATE(14), 1,
      aux_sym_string_repeat1,
    ACTIONS(60), 2,
      sym__string_byte,
      sym_escape_sequence,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
  [130] = 4,
    ACTIONS(62), 1,
      anon_sym_DQUOTE,
    STATE(15), 1,
      aux_sym_string_repeat1,
    ACTIONS(64), 2,
      sym__string_byte,
      sym_escape_sequence,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
  [147] = 4,
    ACTIONS(66), 1,
      anon_sym_DQUOTE,
    STATE(15), 1,
      aux_sym_string_repeat1,
    ACTIONS(68), 2,
      sym__string_byte,
      sym_escape_sequence,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
  [164] = 2,
    ACTIONS(71), 1,
      sym_bin_literal,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
  [174] = 2,
    ACTIONS(71), 1,
      sym_oct_literal,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
  [184] = 2,
    ACTIONS(71), 1,
      sym_hex_literal,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
  [194] = 2,
    ACTIONS(73), 1,
      ts_builtin_sym_end,
    ACTIONS(3), 4,
      sym_line_comment,
      sym_block_comment,
      sym_nested_comment,
      sym_todo_comment,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(6)] = 0,
  [SMALL_STATE(7)] = 19,
  [SMALL_STATE(8)] = 38,
  [SMALL_STATE(9)] = 53,
  [SMALL_STATE(10)] = 68,
  [SMALL_STATE(11)] = 83,
  [SMALL_STATE(12)] = 98,
  [SMALL_STATE(13)] = 113,
  [SMALL_STATE(14)] = 130,
  [SMALL_STATE(15)] = 147,
  [SMALL_STATE(16)] = 164,
  [SMALL_STATE(17)] = 174,
  [SMALL_STATE(18)] = 184,
  [SMALL_STATE(19)] = 194,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_design_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 1, 0, 0),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_design_file, 1, 0, 0),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 2, 0, 0),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_design_file_repeat1, 2, 0, 0),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_design_file_repeat1, 2, 0, 0), SHIFT_REPEAT(13),
  [36] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_design_file_repeat1, 2, 0, 0), SHIFT_REPEAT(16),
  [39] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_design_file_repeat1, 2, 0, 0), SHIFT_REPEAT(17),
  [42] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_design_file_repeat1, 2, 0, 0), SHIFT_REPEAT(2),
  [45] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_design_file_repeat1, 2, 0, 0), SHIFT_REPEAT(18),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 3, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3, 0, 0),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_literal, 4, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [66] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 2, 0, 0),
  [68] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 2, 0, 0), SHIFT_REPEAT(15),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [73] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

enum ts_external_scanner_symbol_identifiers {
  ts_external_token_line_comment = 0,
  ts_external_token_block_comment = 1,
  ts_external_token_nested_comment = 2,
  ts_external_token_todo_comment = 3,
  ts_external_token_identifier = 4,
  ts_external_token__string_byte = 5,
  ts_external_token_escape_sequence = 6,
  ts_external_token_bin_prefix = 7,
  ts_external_token_bin_literal = 8,
  ts_external_token_oct_prefix = 9,
  ts_external_token_oct_literal = 10,
  ts_external_token_dec_literal = 11,
  ts_external_token_hex_prefix = 12,
  ts_external_token_hex_literal = 13,
  ts_external_token_exponent = 14,
  ts_external_token_error_sentinel = 15,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_line_comment] = sym_line_comment,
  [ts_external_token_block_comment] = sym_block_comment,
  [ts_external_token_nested_comment] = sym_nested_comment,
  [ts_external_token_todo_comment] = sym_todo_comment,
  [ts_external_token_identifier] = sym_identifier,
  [ts_external_token__string_byte] = sym__string_byte,
  [ts_external_token_escape_sequence] = sym_escape_sequence,
  [ts_external_token_bin_prefix] = sym_bin_prefix,
  [ts_external_token_bin_literal] = sym_bin_literal,
  [ts_external_token_oct_prefix] = sym_oct_prefix,
  [ts_external_token_oct_literal] = sym_oct_literal,
  [ts_external_token_dec_literal] = sym_dec_literal,
  [ts_external_token_hex_prefix] = sym_hex_prefix,
  [ts_external_token_hex_literal] = sym_hex_literal,
  [ts_external_token_exponent] = sym_exponent,
  [ts_external_token_error_sentinel] = sym_error_sentinel,
};

static const bool ts_external_scanner_states[9][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_line_comment] = true,
    [ts_external_token_block_comment] = true,
    [ts_external_token_nested_comment] = true,
    [ts_external_token_todo_comment] = true,
    [ts_external_token_identifier] = true,
    [ts_external_token__string_byte] = true,
    [ts_external_token_escape_sequence] = true,
    [ts_external_token_bin_prefix] = true,
    [ts_external_token_bin_literal] = true,
    [ts_external_token_oct_prefix] = true,
    [ts_external_token_oct_literal] = true,
    [ts_external_token_dec_literal] = true,
    [ts_external_token_hex_prefix] = true,
    [ts_external_token_hex_literal] = true,
    [ts_external_token_exponent] = true,
    [ts_external_token_error_sentinel] = true,
  },
  [2] = {
    [ts_external_token_line_comment] = true,
    [ts_external_token_block_comment] = true,
    [ts_external_token_nested_comment] = true,
    [ts_external_token_todo_comment] = true,
    [ts_external_token_bin_prefix] = true,
    [ts_external_token_oct_prefix] = true,
    [ts_external_token_dec_literal] = true,
    [ts_external_token_hex_prefix] = true,
  },
  [3] = {
    [ts_external_token_line_comment] = true,
    [ts_external_token_block_comment] = true,
    [ts_external_token_nested_comment] = true,
    [ts_external_token_todo_comment] = true,
    [ts_external_token_bin_prefix] = true,
    [ts_external_token_oct_prefix] = true,
    [ts_external_token_dec_literal] = true,
    [ts_external_token_hex_prefix] = true,
    [ts_external_token_exponent] = true,
  },
  [4] = {
    [ts_external_token_line_comment] = true,
    [ts_external_token_block_comment] = true,
    [ts_external_token_nested_comment] = true,
    [ts_external_token_todo_comment] = true,
    [ts_external_token__string_byte] = true,
    [ts_external_token_escape_sequence] = true,
  },
  [5] = {
    [ts_external_token_line_comment] = true,
    [ts_external_token_block_comment] = true,
    [ts_external_token_nested_comment] = true,
    [ts_external_token_todo_comment] = true,
    [ts_external_token_bin_literal] = true,
  },
  [6] = {
    [ts_external_token_line_comment] = true,
    [ts_external_token_block_comment] = true,
    [ts_external_token_nested_comment] = true,
    [ts_external_token_todo_comment] = true,
    [ts_external_token_oct_literal] = true,
  },
  [7] = {
    [ts_external_token_line_comment] = true,
    [ts_external_token_block_comment] = true,
    [ts_external_token_nested_comment] = true,
    [ts_external_token_todo_comment] = true,
    [ts_external_token_hex_literal] = true,
  },
  [8] = {
    [ts_external_token_line_comment] = true,
    [ts_external_token_block_comment] = true,
    [ts_external_token_nested_comment] = true,
    [ts_external_token_todo_comment] = true,
  },
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_alcha_external_scanner_create(void);
void tree_sitter_alcha_external_scanner_destroy(void *);
bool tree_sitter_alcha_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_alcha_external_scanner_serialize(void *, char *);
void tree_sitter_alcha_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_alcha(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_alcha_external_scanner_create,
      tree_sitter_alcha_external_scanner_destroy,
      tree_sitter_alcha_external_scanner_scan,
      tree_sitter_alcha_external_scanner_serialize,
      tree_sitter_alcha_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
