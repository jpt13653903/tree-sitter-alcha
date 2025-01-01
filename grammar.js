/**
 * @file Alcha grammar for tree-sitter
 * @author John-Philip Taylor
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
    name: 'alcha',

    externals: $ => [
        $.line_comment,
        $.block_comment,
        $.nested_comment,
        $.todo_comment,

        $.identifier,
        $.builtin_const,
        $.builtin_func,
        $.builtin_variable,

        $._string_byte,
        $._interpolated_byte,
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
                $.definition, $.class_definition, $.enum_definition,
                $.alias, $.import, $.struct_definition, $.group_definition, $.access_direction_group,
                $.if_statement, $.for, $.while , $.loop, $.switch, $.case, $.jump,
                $.function_call_statement, $.namespace_push, $.assignment,
                $.rtl, $.fsm, $.hdl,
                $.stimulus, $.emulate, $.fork_join, $.sequence_def, $.assert,
                ';'
            )),

            definition: $ => prec(25, seq(
                optional('inline'),
                choice($.base_type, $._type_identifier),
                optional($.parameter_list),
                optional($.attribute_list),
                choice($.identifier_list, $.function_def, $.operator_overload)
            )),

            class_definition: $ => seq(
                'class', optional($.attribute_list), field('name', $._identifier),
                optional(seq('(', optional($.parameter_def_list), ')')),
                optional(seq(
                    ':', $._type_identifier, optional($.parameter_list),
                    repeat(seq(',', $._type_identifier, optional($.parameter_list)))
                )), $.statement_block
            ),

            access_direction_group: $ => seq(
                choice(
                    $.access_specifier,
                    $.direction_specifier,
                    seq($.access_specifier, $.direction_specifier)
                ), $._statement_block
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

            identifier_list: $ => seq(
                $.variable_def, repeat(seq(',', $.variable_def)), ';'
            ),

            variable_def: $ => seq(
                $._identifier, repeat($.array_definition), optional($.initialiser)
            ),

            function_def: $ => seq(
                seq(field('name', $._identifier), repeat($.array_definition)),
                '(', optional($.parameter_def_list), ')',
                $.statement_block
            ),

            operator_overload: $ => seq(
                seq('operator', $.operator),
                '(', optional($.parameter_def_list), ')',
                $.statement_block
            ),

            operator: $ => choice(
                '?:',
                '|', '~|', '^', '~^', '&', '~&',
                '==', '!=', '<', '>', '<=', '>=',
                '<<', '>>',
                '+', '-', '*', '/', '%', '**', '!',
                '`', '$',
                '..',
                '~', ':', '++', '--',
                '@',
                '=', ':=', '~=', '+=', '-=', '*=', '/=', '**=', '%=', '&=', '|=', '^=', '<<=', '>>=',
                '[*', '[->', '[=', '|->', '|=>', '||', '&&', '&&&'
            ),


            array_definition: $ => seq(
                '[', optional($._expression), ']'
            ),

            initialiser: $ => seq(
                choice('=', ':='), $._expression
            ),

            parameter_def_list: $ => seq(
                $.parameter_def, repeat(seq(',', $.parameter_def))
            ),

            parameter_def: $ => seq(
                optional(seq(choice($.base_type, $._type_identifier), optional($.parameter_list))),
                field('parameter', $._identifier), repeat(seq('[', ']')), optional($.initialiser)
            ),

            attribute_list: $ => seq(
                '<', $.attribute_assignment, repeat(seq(',', $.attribute_assignment)), '>'
            ),

            attribute_assignment: $ => seq(
                $._identifier, '=', $._primary
            ),

            enum_definition: $ => seq(
                'enum', optional($.attribute_list), field('name', $._identifier), $.enum_body
            ),

            enum_body: $ => seq(
                '{', $._enum_member_def, repeat(seq(',', $._enum_member_def)), '}'
            ),

            _enum_member_def: $ => choice(
                field('element', $._identifier),
                $.enum_member_def
            ),

            enum_member_def: $ => seq(
                field('element', $._identifier), '=', field('initialiser', $._expression)
            ),

            _type_identifier: $ => prec(8, choice(
                prec(27, alias($._identifier, $.type_identifier)),
                alias($.member_reference, $.type_identifier),
            )),

        // Statements
            _statement_block: $ => choice(
                $._statement,
                $.statement_block
            ),

            statement_block: $ => seq(
                '{', repeat($._statement), '}'
            ),

            alias: $ => seq(
                'alias', $._identifier, '=', $._expression, ';'
            ),

            import: $ => seq(
                'import', alias($.string, $.filename), optional(seq('as', $._identifier)), ';'
            ),

            struct_definition: $ => seq(
                'struct', optional($.attribute_list), optional(field('name', $._identifier)), $.struct_body
            ),

            struct_body: $ => seq(
                '{', repeat(choice($.definition, $.struct_definition)), '}'
            ),

            group_definition: $ => seq(
                'group', optional($.attribute_list), optional(field('name', $._identifier)), alias($.statement_block, $.group_body)
            ),

            function_call_statement: $ => seq(
                $.function_call, choice(',', ';')
            ),

            namespace_push: $ => prec.left(35, seq(
                $._accessor, '.{', repeat($._statement), '}'
            )),

            assignment: $ => seq(
                $._accessor,
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
                'if', '(', $._expression, ')', $._statement_block, optional(seq('else', $._statement_block))
            )),

            for: $ => seq(
                'for', '(', $._identifier, 'in', $._expression, ')', $._statement_block
            ),

            while: $ => seq(
                'while', '(', $._expression, ')', $._statement_block
            ),

            loop: $ => seq(
                'loop', optional(seq('(', $._expression, ')')), $._statement_block
            ),

            switch: $ => seq(
                'switch', '(', $._expression, ')', $._statement_block
            ),

            case: $ => choice(
                seq('case', '(', $.expression_list, ')', $._statement_block),
                seq('default', $._statement_block),
            ),

            jump: $ => seq(
                choice('return', 'break', 'continue'), optional($._expression), ';'
            ),

            rtl: $ => prec(28, seq(
                'rtl', optional($.parameter_list), optional($.attribute_list), $._statement_block
            )),

            fsm: $ => prec(28, seq(
                'fsm', optional($.parameter_list), optional($.attribute_list), $._statement_block
            )),

            hdl: $ => seq(
                'hdl', $.hdl_files, optional($.attribute_list), $._identifier,
                optional(seq('(', repeat($.assignment), ')')),
                $.hdl_body
            ),

            hdl_files: $ => seq(
                '(', optional(seq(alias($.string, $.filename), repeat(seq(',', alias($.string, $.filename))))), ')'
            ),

            hdl_body: $ => seq(
                '{', repeat(choice(seq(optional($.direction_specifier), $.definition), $.stimulus)), '}'
            ),

        // Expressions
            _expression: $ => prec(8, choice(
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
                $._primary
            )),

            ternary: $ => prec.left(9, choice(
                seq(field('condition', $._expression), '?' , field('true_part', $._expression), ':', field('false_part', $._expression)),
                seq(field('condition', $._expression), '?:',                                         field('false_part', $._expression))
            )),

            bitwise_or: $ => prec.left(10, seq(
                $._expression, choice('|', '~|'), $._expression
            )),

            bitwise_xor: $ => prec.left(11, seq(
                $._expression, choice('^', '~^'), $._expression
            )),

            bitwise_and: $ => prec.left(12, seq(
                $._expression, choice('&', '~&'), $._expression
            )),

            equality: $ => prec.left(13, seq(
                $._expression, choice('==', '!='), $._expression
            )),

            relational: $ => prec.left(14, seq(
                $._expression, choice('<', '>', '<=', '>='), $._expression
            )),

            shift: $ => prec.left(15, seq(
                $._expression, choice('<<', '>>'), $._expression
            )),

            additive: $ => prec.left(16, seq(
                $._expression, choice('+', '-'), $._expression
            )),

            multiplicative: $ => prec.left(17, seq(
                $._expression, choice('*', '/', '%'), $._expression
            )),

            exponential: $ => prec.left(18, seq(
                $._expression, '**', $._expression
            )),

            replication: $ => prec.left(19, seq(
                $._expression, '`', $._primary
            )),

            stringification: $ => prec.left(20, choice(
                seq('$', $._expression),
                seq('$(', $._expression, optional(seq(',', $._expression)), ')'),
            )),

            reduction: $ => prec(21, seq(
                choice('&', '~&', '|', '~|', '^', '~^', '!'), $._expression
            )),

            _range: $ => prec(22, choice(
                $.range,
                $.unary,
                $._accessor
            )),

            range: $ => prec.left(22, seq(
                $._expression, '..', $._expression, optional(seq(':', $._expression))
            )),

            unary: $ => prec(23, seq(
                choice('-', '~', ':', '++', '--'), $._expression
            )),

            _accessor: $ => prec(24, choice(
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
                optional($._expression), "'", $._identifier
            )),

            cast: $ => prec.left(26, seq(
                $._primary, '@', choice(
                    $._identifier,
                    $.literal,
                    seq('(', $.expression_list, ')'),
                )
            )),

            _primary: $ => prec(27, choice(
                $._identifier,
                $.literal,
                'true',
                'false',
                $.vector_concat,
                $.array_concat,
                $.attribute_list,
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
                '[', optional($.expression_list), ']'
            )),

            expression_list: $ => prec.left(31, seq(
                $._expression, repeat(seq(',', $._expression))
            )),

            parameter_list: $ => seq(
                '(', optional(seq($._parameter, repeat(seq(',', $._parameter)))), ')'
            ),

            _parameter: $ => prec(28, choice(
                field('value', $._expression),
                $.assigned_param
            )),

            assigned_param: $ => seq(
                field('parameter', $._identifier), choice('=', ':='), field('value', $._expression)
            ),

        // Verification
            stimulus: $ => seq(
                'stimulus', optional($.parameter_list), optional($.attribute_list),
                optional($._identifier), $.statement_block
            ),

            emulate: $ => seq(
                'emulate', optional($.parameter_list), optional($.attribute_list),
                optional($._identifier), $.statement_block
            ),

            fork_join: $ => seq(
                $.statement_block, repeat1(seq(choice('||', '&&'), $.statement_block))
            ),

            wait: $ => choice(
                seq('wait', '(', $.sequence, ')'),
                seq('@(', $.sensitivity_list, ')'),
                seq(choice('#', '##'), $._primary)
            ),

            sensitivity_list: $ => seq(
                optional(choice('posedge', 'negedge')), $._accessor,
                repeat(seq(',', optional(choice('posedge', 'negedge')), $._accessor))
            ),

            sequence_def: $ => seq(
                'sequence', $._identifier, '{', $.sequence, ';', '}'
            ),

            assert: $ => seq(
                'assert', optional($.parameter_list), $._assert_block
            ),

            _assert_block: $ => choice(
                $._assert_statement,
                $.assert_block
            ),

            assert_block: $ => seq(
                '{', repeat($._assert_statement), '}'
            ),

            _assert_statement: $ => choice(
                alias($.assert_if, $.if),
                seq($.sequence, ';')
            ),

            assert_if: $ => prec.right(seq(
                'if', '(', $._expression, ')', $._assert_block, optional(seq('else', $._assert_block))
            )),

            sequence: $ => prec(2, choice(
                $.implies,
                $.match_or,
                $.match_and,
                $.cycle_delay,
                $.repetition,
                $._expression,
            )),

            implies: $ => prec.right(3, seq(
                $.sequence, choice('|->', '|=>'), $.sequence
            )),

            match_or: $ => prec.left(4, seq(
                $.sequence, '||', $.sequence
            )),

            match_and: $ => prec.left(5, seq(
                $.sequence, choice('&&', '&&&'), $.sequence
            )),

            cycle_delay: $ => prec.left(6, seq(
                field('left', $.sequence), choice('#', '##'), field('delay', $._primary), field('right', $.sequence)
            )),

            repetition: $ => prec.left(7, seq(
                $.sequence, choice('[*', '[->', '[='), $._range, ']'
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
                $.builtin_const,
                $.builtin_func,
                $.builtin_variable
            ),

            string: $ => choice(
                seq('"',  repeat(choice($._string_byte, $.escape_sequence)), '"'),
                seq('$"', repeat(choice(
                    $._interpolated_byte,
                    $.escape_sequence,
                    seq('{', $._expression, optional(seq(',', $._expression)), '}')
                )), '"'),
            ),
    }
});
