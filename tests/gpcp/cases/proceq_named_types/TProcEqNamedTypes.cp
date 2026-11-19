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

(* fixProcEqual: procedure types with matching formal parameter lists are
   equal types (CP report, Appendix A), even when they are denoted by
   different type identifiers.  Values of both types must compare equal. *)
MODULE TProcEqNamedTypes;
  IMPORT CPmain, Console;

  TYPE
    H1 = PROCEDURE (x: INTEGER): INTEGER;
    H2 = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    a: H1;
    b: H2;
    f: H1;

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
  a := Double;
  b := Double;
  f := Double;

  Check(a = b,             "h1-vs-h2-same-proc");
  Check(~(a # b),          "h1-vs-h2-neq");
  Check(a = f,             "h1-vs-h1");
  Check(b = f,             "h2-vs-h1");

  b := NIL;
  Check(a # b,             "nonnil-vs-nil");
  Check(~(a = b),          "nonnil-vs-nil-eq");

  b := Double;
  Check(a = b,             "h1-vs-h2-after-nil")
END TProcEqNamedTypes.
