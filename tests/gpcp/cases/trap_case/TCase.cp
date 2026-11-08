MODULE TCase;
  IMPORT CPmain;
  VAR x: INTEGER;
BEGIN
  x := 5;
  CASE x OF
  | 1: ASSERT(TRUE)
  END
END TCase.
