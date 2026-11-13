(* Strict CP: multidimensional arrays of procedure values. *)
MODULE TMultiArray;
  IMPORT CPmain, Console;

  VAR
    a: ARRAY 2 OF ARRAY 2 OF PROCEDURE (x: INTEGER): INTEGER;

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
  a[0][0] := Double;
  a[1][1] := Triple;

  Check(a[0][0](4) = 8,   "multi-call-00");
  Check(a[1][1](4) = 12,  "multi-call-11");
  Check(a[0][0] = Double, "multi-eq");
  Check(a[1][1] # a[0][0], "multi-neq")
END TMultiArray.
