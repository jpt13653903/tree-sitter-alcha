;-------------------------------------------------------------------------------
;
; Maintainer: jpt13653903
; Capture Reference: https://neovim.io/doc/user/treesitter.html#treesitter-highlight-groups
;-------------------------------------------------------------------------------
;
(line_comment)   @spell @comment
(block_comment)  @spell @comment
(nested_comment) @spell @comment
(todo_comment)   @spell @comment.todo

[
  (bin_prefix)
  (oct_prefix)
  (hex_prefix)
] @type.builtin

[
  (bin_literal)
  (oct_literal)
  (dec_literal)
  (hex_literal)
] @number

(exponent) @property

(imag_suffix) @attribute.builtin

(string) @spell @string
(string
  (escape_sequence) @string.escape)

(identifier) @variable
(builtin_const) @constant.builtin
