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

(* Valid Component Pascal: a procedure value taken from an array element
   can be called directly.  This used to trap in ExprDesc.liveActuals. *)
MODULE TArrayProcCall;
  IMPORT CPmain, Console;

  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    a: ARRAY 3 OF Hook;
    i: INTEGER;

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

  PROCEDURE Run;
    VAR
      b: ARRAY 2 OF Hook;
  BEGIN
    b[0] := Triple;
    b[1] := Double;
    Check(b[0](3) = 9,       "local-array-literal-index");
    i := 1;
    Check(b[i](4) = 8,       "local-array-var-index")
  END Run;

  PROCEDURE Apply(a: ARRAY OF Hook; i: INTEGER; x: INTEGER): INTEGER;
  BEGIN RETURN a[i](x) END Apply;

BEGIN
  a[0] := Double;
  a[1] := Triple;
  a[2] := Double;

  Check(a[0](3) = 6,         "global-array-literal-index");
  i := 1;
  Check(a[i](3) = 9,         "global-array-var-index");
  i := 2;
  Check(a[i](4) = 8,         "global-array-var-index-2");
  Check(a[0](1) + a[1](1) = 5, "two-element-calls");

  Run;

  Check(Apply(a, 0, 5) = 10, "open-array-parameter")
END TArrayProcCall.
