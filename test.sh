export CC=gcc

# touch grammar.js
# touch src/scanner.c

tree-sitter generate --abi 14 && tree-sitter test --show-fields

# tree-sitter generate && tree-sitter parse test/temp.alc

