MODULE TStrictMethodArray;
  TYPE
    T = RECORD n: INTEGER END;
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR t: T; a: ARRAY 2 OF Hook;

  PROCEDURE (VAR self: T) Add(x: INTEGER): INTEGER, NEW;
  BEGIN RETURN self.n + x END Add;

BEGIN
  t.n := 1;
  a[0] := t.Add
END TStrictMethodArray.
