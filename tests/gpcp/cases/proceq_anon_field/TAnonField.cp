(* Strict CP: a record field of an anonymous procedure type. *)
MODULE TAnonField;
  IMPORT CPmain, Console;

  TYPE
    Holder = RECORD cb: PROCEDURE (x: INTEGER): INTEGER END;

  VAR h: Holder;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  h.cb := Double;
  Check(h.cb(3) = 6,   "anon-field-call");
  Check(h.cb = Double, "anon-field-eq")
END TAnonField.
