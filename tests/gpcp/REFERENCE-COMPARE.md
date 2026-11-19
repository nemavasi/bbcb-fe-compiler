# Differential check against the original BlackBox compiler

The `spec_*` suite was compiled with the original BlackBox 1.7.2 compiler
(`BlackBox.exe`, `Dev -> Compile`) under Wine and compared with the patched
GPCP compiler.  The aim is to check **accept/reject parity**, not diagnostic
text: every valid module must be accepted by both compilers, and every case
with `compile-error.txt` must be rejected by both.

## Method

For each module:

1. copy the source to `<BBROOT>/Data/<Module>.Mod` and strip the JVM-only
   `CPmain` import;
2. pre-create the subsystem directories (`<Head>/Code`, `<Head>/Sym`) so the
   compiler does not ask about missing directories;
3. open the document with `BlackBox.exe /O`, focus it and press `Ctrl+K`
   (`Dev -> Compile`);
4. accept a generated `<Head>/Code/<Tail>.ocf` as "accepted"; after the
   timeout (or when no `.ocf` appears) classify the module as "rejected";
5. for multi-module cases compile the dependency first and then the module
   named in `run.txt`.

The helper used for the GUI key injection is a small XTest sender
(`xsend.py`); the reference installation is a plain BlackBox 1.7.2 tree
(`BlackBox.exe` plus `System/`, `Dev/`, `Host/`, ...).

## Results

Valid modules (expected: accepted by both compilers) — all **26/26 OK**:

| Group | Cases |
|---|---|
| lexical | `spec_lex_number`, `spec_lex_string`, `spec_scope_shadow`, `spec_scope_forward_type` |
| constants/types | `spec_const_expr`, `spec_type_array_multi`, `spec_type_record_ext`, `spec_type_guard`, `spec_type_proc_type`, `spec_type_anyptr_anyrec`, `spec_type_domains`, `spec_type_string_short` |
| expressions | `spec_expr_precedence`, `spec_expr_div_mod`, `spec_expr_sets`, `spec_expr_strings` |
| statements | `spec_stmt_case`, `spec_stmt_for`, `spec_stmt_with_else` |
| procedures | `spec_proc_nested_recursion`, `spec_proc_forward`, `spec_proc_method_dispatch`, `spec_proc_method_super` |
| predeclared | `spec_pred_ash`, `spec_pred_bits`, `spec_pred_entier`, `spec_pred_len_size` |
| modules | `spec_module_alias` (A then B), `spec_module_body_order` (A then B) |

Invalid modules (expected: rejected by both compilers) — all **11/11
rejected**:

| Case | Expected error |
|---|---|
| `spec_scope_dup` | duplicate declaration |
| `spec_type_abstract_err` | abstract type instantiated |
| `spec_type_limited_err` | LIMITED record allocated outside its module |
| `spec_stmt_assign_compat` | REAL assigned to INTEGER |
| `spec_proc_in_readonly` | assignment to an IN parameter |
| `spec_proc_result_record` | function result is a record |
| `spec_module_export_write` | assignment to a read-only export |
| `spec_module_private_err` | access to a private identifier |
| `spec_module_cyclic_err` | cyclic import |
| `spec_module_self_err` | module imports itself |

The REAL cases (`spec_real_*`) and the narrowing-conversion cases
(`spec_range_*`) were also accepted by the reference compiler; the
reference emits its own `ranTrap` (134) for the same `Check` paths.  Their run-time expectations (INF for overflow/division by zero,
0 or subnormal for underflow, trap 143 only for NaN) follow report 8.2.2
and the reference's FPU control word (`Kernel.InitFpu` masks overflow,
underflow and zero-divide and traps only invalid operations).

## Reproducing

The comparison needs a BlackBox 1.7.2 installation and a running X server:

```bash
export BBROOT=/path/to/blackbox-1.7.2   # contains BlackBox.exe
export DISPLAY=:0
# compile one module (same GUI sequence as bbcb-fe/tools/wine/ref_build.sh):
#   BlackBox.exe /O Data/<Module>.Mod  ->  focus text  ->  Ctrl+K
```

The pre-existing `bbcb-fe/tools/wine/ref_build.sh` implements the same
sequence; this check only adds the `CPmain` stripping and the multi-module
ordering.
