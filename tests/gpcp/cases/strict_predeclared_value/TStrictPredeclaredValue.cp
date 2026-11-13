MODULE TStrictPredeclaredValue;
  TYPE Hook = PROCEDURE (VAR x: INTEGER);

  VAR f: Hook; n: INTEGER;

BEGIN
  f := INC
END TStrictPredeclaredValue.
