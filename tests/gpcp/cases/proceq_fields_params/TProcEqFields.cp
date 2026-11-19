(*
New BSD License (BSD)
Copyright (c) 2026, nemavasi

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

* Neither my name may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*)

(* fixProcEqual: procedure values stored in record fields, arrays and
   passed through parameters must compare structurally, not by wrapper
   object identity. *)
MODULE TProcEqFields;
  IMPORT CPmain, Console;

  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;
    Holder = RECORD cb: Hook END;

  VAR
    h: Holder;
    f: Hook;
    arr: ARRAY 2 OF Hook;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Same(a: Hook; b: Hook): BOOLEAN;
  BEGIN RETURN a = b END Same;

  PROCEDURE Store(VAR dst: Hook; src: Hook);
  BEGIN dst := src END Store;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  h.cb := Double;
  f := Double;

  Check(h.cb = f,                 "field-vs-var");
  Check(f = h.cb,                 "var-vs-field");
  Check(Same(h.cb, Double),       "param-vs-literal");
  Check(Same(Double, Double),     "two-literal-params");

  Store(f, h.cb);
  Check(f = Double,               "stored-via-varparam");
  Check(f = h.cb,                 "stored-vs-field");

  arr[0] := Double;
  arr[1] := Double;
  Check(arr[0] = arr[1],          "array-elements");
  Check(arr[0] = Double,          "array-vs-literal");

  f := NIL;
  Check(Same(f, NIL),             "nil-param-left");
  Check(Same(NIL, f),             "nil-param-right");
  Check(~Same(f, h.cb),           "nil-vs-field");

  f := Double;
  Check(Same(f, h.cb),            "param-field-var");
  Check(~Same(f, NIL),            "param-vs-nil")
END TProcEqFields.
