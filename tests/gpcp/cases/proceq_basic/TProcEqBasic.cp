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

(* fixProcEqual: structural equality of procedure values on the JVM.
   Kotlin-style model (FunctionReference): two procedure values are equal
   when they denote the same procedure.  NIL keeps its usual meaning.
   Calls through procedure values must keep working. *)
MODULE TProcEqBasic;
  IMPORT CPmain, Console;

  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    f, g: Hook;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Triple(x: INTEGER): INTEGER;
  BEGIN RETURN 3*x END Triple;

  PROCEDURE Apply(cb: Hook; x: INTEGER): INTEGER;
  BEGIN RETURN cb(x) END Apply;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  f := Double;
  g := Double;

  Check(f = g,                 "same-proc-two-vars");
  Check(f = Double,            "var-vs-literal");
  Check(Double = f,            "literal-vs-var");
  Check(Double = Double,       "literal-vs-literal");
  Check(~(f # g),              "not-equal-operator");
  Check(f = f,                 "self");

  Check(f(3) = 6,              "call-through-var");
  Check(Apply(Double, 2) = 4,  "call-through-param");
  Check(Apply(f, 4) = 8,       "call-var-through-param");

  g := Triple;
  Check(f # g,                 "different-procs");
  Check(~(f = g),              "different-procs-eq");

  g := f;
  Check(f = g,                 "copied-var");

  f := NIL;
  Check(f = NIL,               "nil-eq");
  Check(~(f # NIL),            "nil-neq");
  Check(NIL = f,               "nil-left");
  Check(NIL = NIL,             "nil-nil");

  f := Double;
  Check(f # NIL,               "nonnil-neq");
  Check(~(f = NIL),            "nonnil-eq")
END TProcEqBasic.
