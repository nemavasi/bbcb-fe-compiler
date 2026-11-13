MODULE TStrictMethodReturn;
  TYPE
    T = RECORD n: INTEGER END;
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR t: T;

  PROCEDURE (VAR self: T) Add(x: INTEGER): INTEGER, NEW;
  BEGIN RETURN self.n + x END Add;

  PROCEDURE Make(): Hook;
  BEGIN RETURN t.Add END Make;

BEGIN
  t.n := 1;
  ASSERT(Make()(2) = 3)
END TStrictMethodReturn.
