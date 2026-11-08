MODULE TSnap;
  IMPORT CPmain;

  PROCEDURE P;
    VAR
      a1, a2, a3, a4: ARRAY 4 OF INTEGER;
      i: INTEGER;
  BEGIN
    a1[0] := 1; a2[0] := 2; a3[0] := 3; a4[0] := 4;
    i := 7;
    HALT(0)
  END P;

BEGIN
  P
END TSnap.
