# Component Pascal language-spec coverage

Reference: `documentation/CP-Lang.pdf` (Component Pascal Language Report,
Oberon microsystems, 2001/2006).  Each row names at least one executable
case; the case directories live in `tests/gpcp/cases/`.  Cases prefixed
`spec_` were added for this matrix; the older `adr_*`, `oberonc_*`,
`proceq_*`, `procvars_*`, `procsig_*`, `strict_*`, `trap_*` cases are
reused where they already exercise the rule.

| Spec | Rule | Cases |
|---|---|---|
| 3 | identifiers, case sensitivity | `spec_lex_case`, `spec_lex_number` |
| 3 | numbers (decimal, H/L, real, scale) | `spec_lex_number`, `adr046_real_literal` |
| 3 | character constants, strings, quotes | `spec_lex_string`, `adr051_char_string`, `adr180_utf8` |
| 3 | comments, nesting | `spec_lex_comment` |
| 3 | reserved words vs identifiers | `spec_lex_case`, `spec_scope_dup` |
| 4 | scope, shadowing | `spec_scope_shadow` |
| 4 | no duplicate declaration | `spec_scope_dup` (expected error) |
| 4 | forward type references | `spec_scope_forward_type`, `adr048_recursive_type` |
| 4 | export marks `*` and `-` | `spec_module_export_read`, `spec_module_export_write` (error) |
| 4 | private fields / qualified access | `spec_module_private_err` (error), `adr043_private_field` |
| 5 | constant expressions, MAX/MIN/SET | `spec_const_expr`, `oberonc_ConstantFoldingAndLoadOp` |
| 5 | constant folding with LONGINT precision | `spec_const_fold_long` |
| 6.1 | basic types and domains | `spec_type_domains`, `spec_pred_cap_ord_chr` |
| 6.1 | numeric hierarchy, MIN/MAX | `spec_type_domains`, `spec_pred_abs` |
| 6.2 | fixed and multidimensional arrays | `spec_type_array_multi`, `spec_type_array_assign` |
| 6.2 | open arrays and array compatibility | `spec_type_array_open_ptr`, `oberonc_OpenArrays`, `oberonc_OpenArrays2` |
| 6.3 | records, extension, base fields | `spec_type_record_ext`, `spec_type_guard` |
| 6.3 | ABSTRACT / LIMITED | `spec_type_abstract_err` (error), `spec_type_limited_err` (error) |
| 6.3 | ANYREC | `spec_type_anyptr_anyrec`, `adr041_anyrec` |
| 6.4 | pointers, forward pointer types | `spec_scope_forward_type`, `spec_scope_forward_type` |
| 6.4 | NEW, clearing, NIL | `spec_pred_new_clear`, `spec_expr_relations` |
| 6.4 | ANYPTR, FINALIZE | `spec_type_anyptr_anyrec`, `adr025_finalize`, `adr027_anyptr` |
| 6.5 | procedure types, matching parameter lists | `spec_type_proc_type`, `proceq_named_types`, `proceq_multidim_array`, `proceq_array_length`, `proceq_identity` |
| 6.5 | procedures are not values (methods/locals/predeclared) | `strict_method_*`, `strict_nested_*`, `strict_predeclared_value` |
| 6.6 | string types, SHORTCHAR/CHAR | `spec_type_string_short`, `adr051_char_string`, `oberonc_Strings2` |
| 7 | variable declarations, static/dynamic type | `spec_type_record_ext`, `spec_type_guard` |
| 7 | initialization of locals and module variables | `adr019_init_locals`, `spec_pred_new_clear`, `spec_module_body_order` |
| 8.1 | designators, selectors, `^`, `$` | `spec_expr_designator`, `spec_expr_strings` |
| 8.1 | type guards `v(T)` | `spec_type_guard`, `trap_with` |
| 8.2 | precedence and associativity | `spec_expr_precedence` |
| 8.2.1 | logical operators, short-circuit | `spec_expr_shortcircuit` |
| 8.2.2 | arithmetic result types | `spec_expr_precedence`, `spec_real_*` |
| 8.2.2 | DIV/MOD including negative operands | `spec_expr_div_mod`, `trap_div`, `trap_mod` |
| 8.2.2 | real INF/underflow/NaN semantics | `spec_real_div_zero`, `spec_real_overflow`, `spec_real_underflow`, `spec_real_nan` |
| 8.2.3 | set operators and constructors | `spec_expr_sets`, `spec_pred_bits`, `adr020_021_sets` |
| 8.2.4 | string concatenation | `spec_expr_strings`, `spec_stmt_assign_string` |
| 8.2.5 | relations (numeric, char, string, bool, set, pointer, proc, NIL) | `spec_expr_relations`, `spec_str_rel`, `spec_type_proc_type` |
| 8.2.5 | `IN` and `IS` | `spec_expr_sets`, `spec_type_guard` |
| 9.1 | assignment compatibility | `spec_stmt_assign_compat` (error), `spec_type_array_assign`, `oberonc_RecordAssignment2` |
| 9.1/A | `CHR` range check 134; `SHORT` truncation | `spec_range_shortint`, `spec_range_shortint_ok`, `spec_range_byte`, `spec_range_char`, `spec_range_shortchar`, `spec_range_nocheck`, `spec_range_legacy` |
| 9.1 | string assignment length check (trap 136) | `spec_stmt_assign_string` |
| 9.2 | procedure calls, value/VAR/IN/OUT | `spec_proc_params`, `adr028_039_outparams`, `adr049_in_param`, `oberonc_Out*` |
| 9.3 | statement sequences and empty statements | `spec_stmt_empty` |
| 9.4 | IF/ELSIF/ELSE | `spec_stmt_if` |
| 9.5 | CASE labels, ranges, ELSE, no match | `spec_stmt_case`, `trap_case`, `oberonc_CaseNum0`, `oberonc_CaseNum1` |
| 9.6 | WHILE | `spec_stmt_while_repeat` |
| 9.7 | REPEAT executes at least once | `spec_stmt_while_repeat` |
| 9.8 | FOR, TO, BY, descending, zero iterations | `spec_stmt_for`, `trap_for_*`, `oberonc_TestFor`, `oberonc_TestFor1` |
| 9.9 | LOOP/EXIT | `spec_stmt_loop_exit` |
| 9.10 | RETURN in functions and procedures | `spec_proc_nested_recursion`, `adr047_func_end`, `oberonc_TestReturn0` |
| 9.11 | WITH guards and ELSE | `spec_stmt_with_else`, `trap_with` |
| 10 | nested procedures, recursion | `spec_proc_nested_recursion`, `nested_ref_calls` |
| 10 | forward declarations | `spec_proc_forward` |
| 10.1 | formal parameters, IN read-only | `spec_proc_params`, `spec_proc_in_readonly` (error) |
| 10.1 | function result cannot be record/array | `spec_proc_result_record` (error) |
| 10.2 | methods, dynamic dispatch | `spec_proc_method_dispatch`, `adr042_procfield` |
| 10.2 | NEW/EXTENSIBLE, super calls | `spec_proc_method_super` |
| 10.2 | ABSTRACT/EMPTY methods, covariance | `spec_proc_method_abstract`, `adr072_covariant` |
| 10.3 | ABS, ASH, BITS, CAP, CHR, ORD | `spec_pred_abs`, `spec_pred_ash`, `spec_pred_bits`, `spec_pred_cap_ord_chr` |
| 10.3 | ENTIER, LEN, SIZE | `spec_pred_entier`, `spec_pred_len_size` (SIZE is not supported by GPCP; see below), `spec_pred_size_err` |
| 10.3 | LONG/SHORT, MAX/MIN, ODD | `spec_pred_long_short`, `spec_pred_long_short_str`, `spec_pred_short_str_wide`, `spec_pred_short_str_wide_var`, `spec_type_domains`, `spec_pred_odd` |
| 10.3 | INC/DEC/INCL/EXCL, NEW, ASSERT, HALT | `spec_pred_inc_dec_incl_excl`, `spec_pred_new_clear`, `trap_*` |
| 10.4 | FINALIZE | `adr025_finalize` |
| 11 | module body, initialization order, CLOSE | `spec_module_body_order` |
| 11 | import aliases | `spec_module_alias` |
| 11 | read-only exports | `spec_module_export_read`, `spec_module_export_write` (error) |
| 11 | cyclic/self import | `spec_module_cyclic_err`, `spec_module_self_err` (errors) |
| A | same/equal types, type inclusion | `spec_type_proc_type`, `spec_type_domains` |
| A | extension and assignment compatibility | `spec_type_record_ext`, `spec_type_guard`, `spec_stmt_assign_compat` |
| A | array/parameter/expression compatibility | `spec_proc_params`, `spec_expr_precedence` |
| A | constant expressions with maximum precision | `spec_const_fold_long` |
| B | syntax productions | exercised by all `spec_*` cases |
| C | domains of basic types | `spec_type_domains` |
| D | dynamic type info, GC, module loading, Unicode | `spec_type_guard`, `adr025_finalize`, `spec_module_body_order`, `adr180_utf8` |

## Known deviations

* `SIZE(T)` is rejected by GPCP ("SIZE is not meaningful in this
  implementation"), so the `spec_pred_len_size` case covers `LEN` only
  and `spec_pred_size_err` pins the diagnostic.  The language report
  permits `SIZE` but leaves its value implementation-defined; the
  reference BlackBox accepts it.
* `LONG`/`SHORT` on string values are not accepted by GPCP; the
  `spec_pred_long_short` case covers the numeric forms.  The reference
  BlackBox accepts the string forms.
* `FOR` counter overflow is a GPCP checked-arithmetic extension; the
  report defines the counter progression without specifying a trap.
