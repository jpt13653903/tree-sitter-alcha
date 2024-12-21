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
        $.builtin_const,

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
        // Module
            design_file: $ => repeat(seq($._expression, ';')),

        // Expressions
            _expression: $ => prec(10, choice(
                $.ternary,
                $.bitwise_or,
                $.bitwise_xor,
                $.bitwise_and,
                $.bitwise_or,
                $.bitwise_xor,
                $.bitwise_and,
                $.equality,
                $.relational,
                $.shift,
                $.additive,
                $.multiplicative,
                $.exponential,
                $.replication,
                $.stringification,
                $.reduction,
                $.range,
                $.unary,
                $.postfix,
                $.slice,
                $.function_call,
                $.member_reference,
                $.attribute_reference,
                $.cast,
                $._primary,
            )),

            ternary: $ => prec.left(11, choice(
                seq(field('condition', $._expression), '?' , field('true_part', $._expression), ':', field('false_part', $._expression)),
                seq(field('condition', $._expression), '?:',                                         field('false_part', $._expression))
            )),

            bitwise_or: $ => prec.left(12, seq(
                $._expression, choice('|', '~|'), $._expression
            )),

            bitwise_xor: $ => prec.left(12, seq(
                $._expression, choice('^', '~^'), $._expression
            )),

            bitwise_and: $ => prec.left(13, seq(
                $._expression, choice('&', '~&'), $._expression
            )),

            equality: $ => prec.left(14, seq(
                $._expression, choice('==', '!='), $._expression
            )),

            relational: $ => prec.left(15, seq(
                $._expression, choice('<', '>', '<=', '>='), $._expression
            )),

            shift: $ => prec.left(16, seq(
                $._expression, choice('<<', '>>'), $._expression
            )),

            additive: $ => prec.left(17, seq(
                $._expression, choice('+', '-'), $._expression
            )),

            multiplicative: $ => prec.left(18, seq(
                $._expression, choice('*', '/', '%'), $._expression
            )),

            exponential: $ => prec.left(19, seq(
                $._expression, '**', $._expression
            )),

            replication: $ => prec.left(20, seq(
                $._expression, '`', $._primary
            )),

            stringification: $ => prec.left(20, choice(
                seq('$', $._expression),
                seq('$(', $._expression, optional(seq(',', $._expression)), ')'),
            )),

            reduction: $ => prec(21, seq(
                choice('&', '~&', '|', '~|', '^', '~^', '!'), $._expression
            )),

            range: $ => prec.left(22, seq(
                $._expression, '..', $._expression, optional(seq(':', $._expression))
            )),

            unary: $ => prec(23, seq(
                repeat1(choice('-', '~', ':', '++', '--')), $._expression
            )),

            postfix: $ => prec.left(24, choice(
                seq($._expression, '++'),
                seq($._expression, '--'),
                seq($._expression, '!')
            )),

            slice: $ => prec.left(25, seq(
                $._expression, $.array
            )),

            function_call: $ => prec.left(25, seq(
                $._expression, $.parameter_list
            )),

            member_reference: $ => prec.left(25, seq(
                $._expression, choice('.', '?.'), $._identifier
            )),

            attribute_reference: $ => prec.left(25, seq(
                $._expression, "'", $._identifier
            )),

            cast: $ => prec.left(26, seq(
                $._primary, '@', choice(
                    $._identifier,
                    $.literal,
                    seq('(', $.expression_list, ')'),
                )
            )),

            _primary: $ => prec(27, choice(
                seq(optional("'"), $._identifier),
                $.literal,
                'true',
                'false',
                $.vector_concat,
                $.array_concat,
                $.array,
                $.string,
                seq('(', $._expression, ')'),
            )),

            vector_concat: $ => prec(28, seq(
                ':(', $.expression_list, ')'
            )),

            array_concat: $ => prec(29, seq(
                ':[', $.expression_list, ']'
            )),

            array: $ => prec(30, seq(
                '[', $.expression_list, ']'
            )),

            expression_list: $ => prec.left(31, seq(
                $._expression, repeat(seq(',', $._expression))
            )),

            parameter_list: $ => prec(32, seq(
                '(', optional(seq($._parameter, repeat(seq(',', $._parameter)))), ')'
            )),

            _parameter: $ => prec(33, choice(
                field('value', $._expression),
                $.assigned_param
            )),

            assigned_param: $ => prec(34, seq(
                field('parameter', $._identifier), choice('=', ':='), field('value', $._expression)
            )),

        // Scanner
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

            _identifier: $ => choice(
                $.identifier,
                $.builtin_const
            ),

            string: $ => seq('"', repeat(choice($._string_byte, $.escape_sequence)), '"'),
    }
});
