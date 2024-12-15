/**
 * @file Alcha grammar for tree-sitter
 * @author John-Philip Taylor
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
    name: "alcha",

    externals: $ => [
        $.line_comment,
        $.block_comment,
        $.nested_comment,
        $.todo_comment,

        $.identifier,

        $._string_byte,
        $.escape_sequence,

        $.bin_prefix,
        $.bin_literal,

        $.oct_prefix,
        $.oct_literal,

        $.dec_literal,

        $.hex_prefix,
        $.hex_literal,

        $.exponent,
        $.imag_suffix,

        $.error_sentinel
    ],

    extras: $ => [
        $.line_comment,
        $.block_comment,
        $.nested_comment,
        $.todo_comment,
        /\s+/
    ],

    rules: {
        design_file: $ => repeat(choice(
            $.literal,
            $.string,
            $.identifier
        )),

        literal: $ => seq(
            choice(
                seq($.bin_prefix, $.bin_literal),
                seq($.oct_prefix, $.oct_literal),
                                  $.dec_literal,
                seq($.hex_prefix, $.hex_literal),
            ),
            optional($.exponent),
            optional($.imag_suffix)
        ),

        string: $ => seq('"', repeat(choice($._string_byte, $.escape_sequence)), '"'),
    }
});
