(* Strict CP: a value parameter of an anonymous procedure type. *)
MODULE TAnonParam;
  IMPORT CPmain, Console;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Apply(cb: PROCEDURE (x: INTEGER): INTEGER; x: INTEGER): INTEGER;
  BEGIN RETURN cb(x) END Apply;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  Check(Apply(Double, 4) = 8, "anon-value-param")
END TAnonParam.
