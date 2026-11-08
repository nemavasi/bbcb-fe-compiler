MODULE TAssertSnap;
  IMPORT CPmain;

  PROCEDURE P;
    VAR a1, a2: INTEGER;
  BEGIN
    a1 := 1;
    a2 := 2;
    ASSERT(FALSE, 20)
  END P;

BEGIN
  P
END TAssertSnap.
