# Оставшиеся работы

Состояние на момент записи:

- `main` = `c20429f` (влит `longstr`), `tests/gpcp` — **216/216**;
- текущая работа: `strcmpFix` (фикс `>` на строковых константах);
- `bbcb-fe/ci/pinned.txt` обновляется на HEAD ветки `strcmpFix`;
- REAL-семантика приведена к отчёту 8.2.2 и `Kernel.InitFpu`
  (overflow → `INF`, underflow → `0`/subnormal, `1.0/0.0` → `INF`,
  трап только `143` для NaN).

Ниже — приоритизированный список того, что ещё не закрыто.

## P0 — неверное поведение

- [x] **`>` на строковых константах всегда `FALSE`.**
  В `ExprDesc.strOp` свёртка использовала `sRes > 1` вместо `> 0`
  (`L.strCmp` возвращает -1/0/1); в `CPJrts.strCmp` вторая ветка
  проверяла `l.length < r.length` вместо `>`. Исправлено, тест
  `spec_str_rel` (198/198).

- [x] **Trap 134 для сужающих преобразований.**
  Реализовано в ветке `trap134`: `CPJrts.RangeCheckI`, RTS-индекс
  `ChkI` во всех эмиттерах, проверки в `ConvertDn` и гейт `-nocheck`.
  `LONGINT → INTEGER` по отчёту — усечение, без проверки.
  Тесты: `spec_range_*` (197/197).

- [ ] **Платформенные трапы с «сырыми» сообщениями дают `-1`.**
  `blackbox/System/Mod/java/CP/Kernel/Traps.java:172` (`codeOf`) не
  разбирает `#143: ...`, `ASSERT 20: ...`, `#id: ...`. Затронуты
  `Math.Sqrt/Ln/Log/Power/...`, `Kernel.FatalError`,
  `Kernel.Call/NewRec/NewArr`. Либо парсить сообщение, либо бросать
  `TrapError` в этих точках.

- [ ] **`Kernel.FatalError` семантика.**
  Эталон: MessageBox + `ExitProcess(1)`. У нас: трап `-1`, приложение
  продолжает работу. Для ошибок `StdLoader` это опасно.

- [ ] **Trap 131 (`function without RETURN`).**
  Эталон трапает 131; GPCP даёт compile-time warning 136 и
  `PushJunkAndReturn` (возврат нуля/junk). ADR-047.

- [ ] **Stack overflow (137).**
  Эталон откладывает `TrapCleanup`, затем `DefaultTrapViewer` +
  `ResetStackGuard`. У нас `Traps.handle` сразу делает
  `drainTrapCleaners()` — риск рекурсивного переполнения в cleanup.

- [ ] **133 (implied type guard) не отличается от 132.**
  На JVM оба идут через `ClassCastException` → 132.

## P1 — отступления от спецификации

- [ ] **`SIZE(T)` не реализован.**
  `sources/gpcp/ExprDesc.cp:1401`: `Builtin.sizeP → ExprError(167)`.
  Причина — нет единой модели памяти на JVM/.NET. Если нужен паритет с
  BlackBox, задать фиксированную CP-раскладку (x86-подобную), а не
  реальный размер JVM-объекта.

- [x] **`LONG`/`SHORT` на строках.**
  Вариант A: `LONG`/`SHORT` получили строковые ветки; `SHORT` wide-string
  проверяется через `ChrArrCheck` (trap 134), литералы копируются через
  `StrToChrs`.  Тесты `spec_pred_long_short_str`,
  `spec_pred_short_str_wide`, `spec_pred_short_str_wide_var`.
  Литералы по-прежнему типизируются как `String` (6.6 — возможный
  follow-up, вариант B).

- [x] **FOR-overflow.**
  Проверено: BlackBox превращает `FOR` в `INC`; `INTO` эмитится только
  с `+` (`allchecks`), поэтому по умолчанию счётчик заворачивается, а с
  `+` — трап 138.  GPCP проверяет по умолчанию (`-nocheck` отключает) —
  это осознанное расширение.  Покрыты non-simple `FOR` (переменные
  границы, ветка `topV`), `BY 3`/`-3`/`4`, `LONGINT` и `-nocheck`.
  Заодно исправлен `AsmUtil.newLongLocal` (стек-карты LONGINT `FOR`).

- [ ] **REAL 140–142.**
  После приведения к отчёту они больше не возникают по умолчанию;
  `Traps.explain` всё ещё содержит их тексты (мёртвые ветки).

## P2 — пробелы в тестах

- [ ] Reference comparison — только accept/reject; runtime эталона не
  сравнивался, harness (Wine + BlackBox + XTest) вне репозитория.
- [x] `-jasmin` — добавлены compile-only тесты `trap_case_jasmin` и
  `trap_with_jasmin` (полный Jasmin-runtime не проверяется).
- [x] `-legacy` — добавлены `trap_case_legacy` и `trap_with_legacy`.
- [ ] Снапшоты: `smoke_trap` теперь проверяет значения и боксинг скалярных
  типов (`TrapValues`); OUT-скаляры, `CASE`/`WITH`, module body и
  legacy/jasmin по-прежнему не имеют полного снапшота.
- [x] Тесты на 134 (`spec_range_*`; `SHORT` — усечение, `CHR` — 134),
  137 (`smoke_trap`, `stack`), `SIZE` (`spec_pred_size_err`).
- [ ] Нет тестов на 131 и `FatalError`.
- [x] non-simple FOR и `BY ±2` — `spec_stmt_for_var`.

## P3 — платформа и воспроизводимость

- [ ] `Traps.run` используется только в mouse-tracker; меню,
  `Dialog.Call`, `EventQueue`, `Kernel.Try` идут через `Traps.handle`.
  Решить, нужен ли `run` (LIFO cleanup + guard) на остальных границах.
- [ ] Java-trace не показывается в окне трапа — только CP-кадры; трейс
  есть в `TrapError.javaTrace`/stderr.
- [ ] `cprts.jar` не пиннится хешем: в `ci/pinned.txt` только
  `compiler.cprts.generated = yes`.
- [ ] 1833 сгенерированных файла всё ещё в git (`libs/`, `symfiles/`).
- [ ] `bbcb-fe` смотрит на `6dc5eee`; прогнать `smoke_selfbuild` и
  `smoke_trap` на этой ревизии, если ещё не прогоняли.

## P4 — остаточное по strict CP

- [x] `procEnv` удалён из `ProcKey`; обёртки `Proc$Lit$` его больше не
  генерируют (strict CP не захватывает окружение).
- [x] Структурное имя `CP/$T/P…` включает длину fixed-массива и явный
  маркер open/fixed; тест `proceq_array_length`.
- [x] `hashCode` проверяется Java-probe `proceq_identity` (`equals` ⇒ равный
  `hashCode`, разные host-классы для разных сигнатур, отсутствие `procEnv`).
- [ ] ADR-015 (super call к implement-only), ADR-040 (вложенный `WITH`),
  ADR-050 (weak `.cps`) — документированно не закрыты.
