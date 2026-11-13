MODULE TStrictMethodCompare;
  TYPE
    T = RECORD n: INTEGER END;
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR t: T;

  PROCEDURE (VAR self: T) Add(x: INTEGER): INTEGER, NEW;
  BEGIN RETURN self.n + x END Add;

BEGIN
  t.n := 1;
  IF t.Add = t.Add THEN ASSERT(TRUE) END
END TStrictMethodCompare.
