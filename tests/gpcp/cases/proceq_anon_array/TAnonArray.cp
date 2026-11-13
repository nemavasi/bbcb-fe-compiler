(* Strict CP: arrays of an anonymous procedure type. *)
MODULE TAnonArray;
  IMPORT CPmain, Console;

  VAR
    a: ARRAY 2 OF PROCEDURE (x: INTEGER): INTEGER;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Triple(x: INTEGER): INTEGER;
  BEGIN RETURN 3*x END Triple;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  a[0] := Double;
  a[1] := Triple;

  Check(a[0](5) = 10,  "anon-array-call-0");
  Check(a[1](5) = 15,  "anon-array-call-1");
  Check(a[0] = Double, "anon-array-eq");
  Check(a[1] # a[0],   "anon-array-neq")
END TAnonArray.
