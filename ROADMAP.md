# Оставшиеся работы

Состояние на момент записи:

- `main` = `6dc5eee` (влит `tests2`), `tests/gpcp` — **190/190**;
- `bbcb-fe/ci/pinned.txt` указывает на `6dc5eee`;
- REAL-семантика приведена к отчёту 8.2.2 и `Kernel.InitFpu`
  (overflow → `INF`, underflow → `0`/subnormal, `1.0/0.0` → `INF`,
  трап только `143` для NaN).

Ниже — приоритизированный список того, что ещё не закрыто.

## P0 — неверное поведение

- [ ] **Trap 134 для сужающих преобразований.**
  `sources/gpcp/JavaUtil.cp:2242-2267` (`ConvertDn`) содержит
  `(* jf.RangeCheck(...); STILL TO DO *)`.
  Не проверяются `INTEGER → SHORTINT/BYTE/CHAR/SHORTCHAR`
  (и `CHAR → SHORTCHAR`). В эталоне это `ranTrap` → **134**.
  MSIL-бэкенд уже умеет (`conv.ovf.*`). Нужен runtime-хелпер
  `CPJrts.RangeCheckI`, RTS-индексы во всех эмиттерах и гейт `-nocheck`.
  `LONGINT → INTEGER` по отчёту — усечение, без проверки.

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

- [ ] **`LONG`/`SHORT` на строках.**
  GPCP не принимает `LONG("ab")` / `SHORT("ab")`; эталон принимает.
  Числовые формы работают.

- [ ] **FOR-overflow.**
  Это расширение GPCP. Не проверено на эталоне, трапает ли BlackBox при
  переполнении счётчика. Не покрыты non-simple `FOR` (ветка `topV`) и
  `BY ≠ ±1`.

- [ ] **REAL 140–142.**
  После приведения к отчёту они больше не возникают по умолчанию;
  `Traps.explain` всё ещё содержит их тексты (мёртвые ветки).

## P2 — пробелы в тестах

- [ ] Reference comparison — только accept/reject; runtime эталона не
  сравнивался, harness (Wine + BlackBox + XTest) вне репозитория.
- [ ] `-jasmin` — нет end-to-end trap-теста (нужен Jasmin).
- [ ] `-legacy` — покрыты `HALT`/`ASSERT`, но не `CASE`/`WITH`.
- [ ] Снапшоты: OUT-скаляры не попадают; VAR-скаляры показывают значение
  на входе; `CASE`/`WITH` снапшот не передают; тело модуля/legacy/jasmin —
  `null`; тесты проверяют только имена, не значения/боксинг.
- [ ] Нет тестов на 134, 131, 137, `FatalError`, `SIZE`, range-check,
  non-simple FOR/BY.

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

- [ ] `procEnv` в strict всегда `NIL` — мёртвый метод в `ProcKey`.
- [ ] Структурное имя `CP/$T/P…` не включает длину массива и
  open/fixed-различие.
- [ ] `hashCode` процедурных значений наблюдаемо не проверяется.
- [ ] ADR-015 (super call к implement-only), ADR-040 (вложенный `WITH`),
  ADR-050 (weak `.cps`) — документированно не закрыты.
