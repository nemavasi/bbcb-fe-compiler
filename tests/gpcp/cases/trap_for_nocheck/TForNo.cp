MODULE TForNo;
  IMPORT CPmain, Console;
  VAR i: INTEGER;

  PROCEDURE P;
  BEGIN
    FOR i := MAX(INTEGER)-1 TO MAX(INTEGER) DO
      IF i < 0 THEN RETURN END
    END
  END P;

BEGIN
  P;
  Console.WriteLn()
END TForNo.
