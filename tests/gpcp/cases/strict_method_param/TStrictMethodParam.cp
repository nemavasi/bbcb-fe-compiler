MODULE TStrictMethodParam;
  TYPE
    T = RECORD n: INTEGER END;
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR t: T;

  PROCEDURE (VAR self: T) Add(x: INTEGER): INTEGER, NEW;
  BEGIN RETURN self.n + x END Add;

  PROCEDURE Apply(cb: Hook; x: INTEGER): INTEGER;
  BEGIN RETURN cb(x) END Apply;

BEGIN
  t.n := 1;
  ASSERT(Apply(t.Add, 2) = 3)
END TStrictMethodParam.
