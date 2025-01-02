# tree-sitter-alcha

[![CI][ci]](https://github.com/jpt13653903/tree-sitter-alcha/actions/workflows/ci.yml)
[![discord][discord]](https://discord.gg/w7nTvsVJhm)
[![matrix][matrix]](https://matrix.to/#/#tree-sitter-chat:matrix.org)

A Tree-sitter parser for ALCHA files.

## References

- [ALCHA Repository][alcha]

## Setup Process

Configure your `treesitter.lua` (or equivalent) as follows:

```lua
local parser_config = require('nvim-treesitter.parsers').get_parser_configs()

parser_config.alcha = {
  install_info = {
    url = "https://github.com/jpt13653903/tree-sitter-alcha.git",
    files = { 'src/parser.c', 'src/scanner.c' },
    branch = 'master',
    generate_requires_npm = false,
    requires_generate_from_grammar = false,
  },
  filetype = 'alcha',
}

local treesitter = require('nvim-treesitter.configs')

treesitter.setup {
  ensure_installed = {
    -- Some list of languages...
    'alcha',
    -- Some more languages...
  },

  -- Some other options and configuration...
}
```

Then copy the contents of the `queries` folder to your `after/queries/alcha`
configuration folder, typically `~/.config/nvim/after/queries/alcha` on Linux
and `~/AppData/Local/nvim/after/queries/alcha/` on Windows.

Finally, run `:TSUpdate`.

## Building

- Follow the instructions [here][ts-docs] to setup your development environment.
- Run `npm install --save-dev tree-sitter-cli`
- Add `node_modules/.bin` to your environment path
- Run `tree-sitter generate`
- Run `tree-sitter test`

[alcha]: https://github.com/jpt13653903/ALCHA
[ci]: https://img.shields.io/github/actions/workflow/status/jpt13653903/tree-sitter-alcha/ci.yml?logo=github&label=CI
[discord]: https://img.shields.io/discord/1063097320771698699?logo=discord&label=discord
[matrix]: https://img.shields.io/matrix/tree-sitter-chat%3Amatrix.org?logo=matrix&label=matrix
[ts-docs]: https://tree-sitter.github.io/tree-sitter/creating-parsers#getting-started

