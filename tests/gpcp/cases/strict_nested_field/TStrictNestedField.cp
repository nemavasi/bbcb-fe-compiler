MODULE TStrictNestedField;
  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;
    Holder = RECORD cb: Hook END;

  VAR h: Holder;

  PROCEDURE Outer;
    PROCEDURE Inner(x: INTEGER): INTEGER;
    BEGIN RETURN x + 1 END Inner;
  BEGIN
    h.cb := Inner
  END Outer;

BEGIN
  Outer
END TStrictNestedField.
