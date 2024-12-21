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
(builtin_func) @function.builtin

[
  "true"
  "false"
] @constant.builtin

[
  "rtl"
  "fsm"
  "hdl"
] @keyword

[
  "wait"
] @keyword.coroutine

[
  "func"
] @keyword.function

[
  "posedge"
  "negedge"
] @keyword.operator

[
  "import"
  "as"
] @keyword.import

[
  "void"
  "auto"
  "pin"
  "net"
  "byte"
  "char"
  "num"
  "class"
  "enum"
  "struct"
  "group"
] @keyword.type

[
  "input"
  "output"
  "public"
  "private"
  "protected"
  "inline"
] @keyword.modifier

[
  "for"
  "in"
  "while"
  "loop"
] @keyword.repeat

[
  "return"
  "break"
  "continue"
  "goto"
] @keyword.return

[
  "stimulus"
  "emulate"
  "assert"
] @keyword.debug

[
  "if"
  "else"
  "switch"
  "case"
  "default"
] @keyword.conditional

[
  "alias"
] @keyword.directive.define

[
  "++"
  "--"
  ".."
  ":"
  "&"
  "~&"
  "|"
  "~|"
  "^"
  "~^"
  "~"
  "!"
  ":("
  ":["
  "`"
  "+"
  "-"
  "*"
  "/"
  "%"
  "**"
  "<<"
  ">>"
  "<"
  ">"
  "<="
  ">="
  "=="
  "!="
  "?"
  "?:"
  "?."
  "="
  ":="
  "~="
  "+="
  "-="
  "*="
  "/="
  "%="
  "^="
  "&="
  "|="
  "**="
  "<<="
  ">>="
  "$"
  "$("
  "@"
  "#"
  "##"
  ; "[*"
  ; "[->"
  ; "[="
  ; "|->"
  ; "|=>"
  "||"
  "&&"
  ; "&&&"
] @operator

[
  "."
  "'"
  ".{"
  ","
  ";"
] @punctuation.delimiter

[
  "("
  ")"
  "["
  "]"
  "{"
  "}"
] @punctuation.bracket

(attribute_list
  "<" @punctuation.bracket
  ">" @punctuation.bracket)

(type_identifier) @type
(class_definition
  name: (identifier) @type)

(function_call) @function.call
(function_def
  name: (identifier) @function)

