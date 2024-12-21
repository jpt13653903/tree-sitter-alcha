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
        $.builtin_func,

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

    conflicts: $ => [
        [$.access_direction_group],
        [$._type_identifier, $._expression],
        [$._type_identifier, $._primary]
    ],

    rules: {
        // Module
            module: $ => repeat($._statement),

            _statement: $ => seq(optional($.wait), choice(
                $.label, $.definition, $.class_definition, $.enum_definition,
                $.alias, $.import, $.struct, $.group, $.access_direction_group,
                $.if_statement, $.for, $.while , $.loop, $.switch, $.jump, $.goto,
                $.function_call_statement, $.namespace_push, $.assignment,
                $.rtl, $.fsm, $.hdl,
                $.stimulus, $.emulate, $.fork_join, $.assert,
                ';'
            )),

            label: $ => seq(
                $._identifier, ':'
            ),

            definition: $ => prec(25, seq(
                choice($.base_type, $._type_identifier), optional($.parameter_list), optional($.attribute_list), $.identifier_list,
            )),

            class_definition: $ => seq(
                'class', optional($.attribute_list), field('name', $._identifier),
                optional(seq('(', optional($.def_parameter_list), ')')),
                optional(seq(
                    ':', $._type_identifier, optional($.parameter_list),
                    repeat(seq(',', $._type_identifier, optional($.parameter_list)))
                )), '{', repeat($._statement), '}'
            ),

            access_direction_group: $ => seq(
                choice(
                    $.access_specifier,
                    $.direction_specifier,
                    seq($.access_specifier, $.direction_specifier)
                ), $.statement_block
            ),

            access_specifier: $ => choice(
                'public', 'private', 'protected'
            ),

            direction_specifier: $ => choice(
                'input', 'output'
            ),

            base_type: $ => choice(
                'pin',  'net',
                'void', 'auto',
                'byte', 'char', 'num',
                'func'
            ),

            identifier_list: $ => choice(
                    $.function_def,
                    seq($.variable_def, repeat(seq(',', $.variable_def)), ';')
            ),

            variable_def: $ => seq(
                $._identifier, repeat($.array_definition), optional($.initialiser)
            ),

            function_def: $ => seq(
                optional('inline'), choice(
                    seq(field('name', $._identifier), repeat($.array_definition)),
                    seq('operator', $.operator)
                ),
                '(', optional($.def_parameter_list), ')',
                '{', repeat($._statement), '}'
            ),

            operator: $ => choice(
                '++', '--',
                '&', '~&', '|', '~|', '^', '~^', '~', '!',
                '`', '+', '-', '*', '/', '%', '**',
                '<<', '>>', '<', '>', '<=', '>=', '==', '!=',
                '=', ':=', '~=', '+=', '-=', '*=', '/=', '%=',
                '^=', '&=', '|=', '**=', '<<=', '>>=',
                '@', '||', '&&', '&&&'
            ),

            array_definition: $ => seq(
                '[', optional($._expression), ']'
            ),

            initialiser: $ => seq(
                choice('=', ':='), $._expression
            ),

            def_parameter_list: $ => seq(
                $.def_parameter, repeat(seq(',', $.def_parameter))
            ),

            def_parameter: $ => seq(
                optional(choice($.base_type, $._type_identifier)), $._identifier, repeat(seq('[', ']')), optional($.initialiser)
            ),

            attribute_list: $ => seq(
                '<', $.attribute_assignment, repeat(seq(',', $.attribute_assignment)), '>'
            ),

            attribute_assignment: $ => seq(
                $._identifier, '=', $._primary
            ),

            enum_definition: $ => seq(
                'enum', $._identifier, '{', $._identifier, repeat(seq(',', $._identifier)), '}'
            ),

            _type_identifier: $ => prec(10, choice(
                prec(27, alias($._identifier, $.type_identifier)),
                alias($.member_reference, $.type_identifier),
            )),

        // Statements
            statement_block: $ => choice(
                $._statement,
                seq('{', repeat($._statement), '}')
            ),

            alias: $ => seq(
                'alias', $._identifier, '=', $._expression, ';'
            ),

            import: $ => seq(
                'import', alias($.string, $.filename), optional(seq('as', $._identifier)), ';'
            ),

            struct: $ => seq(
                'struct', optional($.attribute_list), optional($._identifier), '{', repeat(choice($.definition, $.struct)), '}'
            ),

            group: $ => seq(
                'group', optional($.attribute_list), optional($._identifier), '{', repeat($._statement), '}'
            ),

            function_call_statement: $ => seq(
                $.function_call, choice(',', ';')
            ),

            namespace_push: $ => prec.left(35, seq(
                $._postfix, '.{', repeat($._statement), '}'
            )),

            assignment: $ => seq(
                $._postfix,
                choice(
                    seq(
                        choice('=', ':=', '~=', '+=' , '-=' , '*=' , '/=' , '**=', '%=', '&=', '|=', '^=', '<<=', '>>='),
                        $._expression
                    ),
                    '++',
                    '--'
                ),
                choice(',', ';')
            ),

            if_statement: $ => prec.right(seq(
                'if', '(', $._expression, ')', $.statement_block, optional(seq('else', $.statement_block))
            )),

            for: $ => seq(
                'for', '(', $._identifier, 'in', $._expression, ')', $.statement_block
            ),

            while: $ => seq(
                'while', '(', $._expression, ')', $.statement_block
            ),

            loop: $ => seq(
                'loop', optional(seq('(', $._expression, ')')), $.statement_block
            ),

            switch: $ => seq(
                'switch', '(', $._expression, ')', '{',
                repeat(seq(
                    'case', '(', $.expression_list, ')', $.statement_block)),
                optional(seq(
                    'default', $.statement_block
                )), '}'
            ),

            jump: $ => seq(
                choice('return', 'break', 'continue'), optional($._expression), ';'
            ),

            goto: $ => seq(
                'goto', $._identifier, ';'
            ),

            rtl: $ => seq(
                'rtl', optional($.attribute_list), optional($.parameter_list), $.statement_block
            ),

            fsm: $ => seq(
                'fsm', optional($.attribute_list), optional($.parameter_list), $.statement_block
            ),

            hdl: $ => seq(
                'hdl', optional($.attribute_list), $.hdl_files, $._identifier,
                optional(seq('(', repeat($.assignment), ')')),
                '{', repeat(choice($.definition, $.stimulus)), '}'
            ),

            hdl_files: $ => seq(
                '(', optional(seq(alias($.string, $.filename), repeat(seq(',', alias($.string, $.filename))))), ')'
            ),

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

            _postfix: $ => prec(24, choice(
                $._primary,
                $.cast,
                $.slice,
                $.function_call,
                $.member_reference,
                $.attribute_reference
            )),

            postfix: $ => prec.left(24, choice(
                seq($._expression, '++'),
                seq($._expression, '--'),
                seq($._expression, '!')
            )),

            slice: $ => prec.left(25, seq(
                $._expression, $.array
            )),

            function_call: $ => prec(25, seq(
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

            parameter_list: $ => seq(
                '(', optional(seq($._parameter, repeat(seq(',', $._parameter)))), ')'
            ),

            _parameter: $ => choice(
                field('value', $._expression),
                $.assigned_param
            ),

            assigned_param: $ => seq(
                field('parameter', $._identifier), choice('=', ':='), field('value', $._expression)
            ),

        // Verification
            stimulus: $ => seq(
                'stimulus', optional($.attribute_list), optional($.parameter_list),
                optional($._identifier), '{', repeat($._statement), '}'
            ),

            emulate: $ => seq(
                'emulate', optional($.attribute_list), optional($.parameter_list),
                optional($._identifier), '{', repeat($._statement), '}'
            ),

            fork_join: $ => seq(
                '{', repeat($._statement), '}', repeat1(seq(choice('||', '&&'), '{', repeat($._statement), '}'))
            ),

            wait: $ => choice(
                seq('wait', '(', $.sequence, ')'),
                seq('@(', $.sensitivity_list, ')'),
                seq(choice('#', '##'), $._primary)
            ),

            sensitivity_list: $ => seq(
                optional(choice('posedge', 'negedge')), $._expression,
                repeat(seq(',', optional(choice('posedge', 'negedge')), $._expression))
            ),

            assert: $ => seq(
                'assert', $.sequence
            ),

            sequence: $ => $._expression,

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
                $.builtin_const,
                $.builtin_func
            ),

            string: $ => seq('"', repeat(choice($._string_byte, $.escape_sequence)), '"'),
    }
});
