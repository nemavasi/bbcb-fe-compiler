(* Strict CP: VAR/OUT parameters of an anonymous procedure type in a
   function, so TypeOfBox must box the anonymous procedure type. *)
MODULE TVarProcAnon;
  IMPORT CPmain, Console;

  VAR
    f: PROCEDURE (x: INTEGER): INTEGER;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Call(VAR y: PROCEDURE (x: INTEGER): INTEGER): INTEGER;
  BEGIN RETURN y(4) END Call;

  PROCEDURE Make(OUT y: PROCEDURE (x: INTEGER): INTEGER): INTEGER;
  BEGIN y := Double; RETURN 7 END Make;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  f := Double;
  Check(Call(f) = 8,  "anon-var-proc-param");
  Check(Make(f) = 7,  "anon-out-proc-param-result");
  Check(f(2) = 4,     "anon-out-proc-param-assigned")
END TVarProcAnon.
