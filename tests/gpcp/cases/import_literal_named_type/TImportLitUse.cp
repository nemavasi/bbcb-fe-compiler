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

(* Stage 3: an imported procedure literal must get the correct JVM method
   descriptor and share the host class of the named exported procedure type.
   Regression for the former `Field ... illegal signature` /
   `ClassFormatError` on the JVM backend. *)
MODULE TImportLitUse;
  IMPORT CPmain, Console, TImportLitLib;

  VAR
    f, g: TImportLitLib.Hook;
    h: PROCEDURE (x: INTEGER): INTEGER;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  f := TImportLitLib.Double;
  Check(f(3) = 6,                         "call-imported-literal");

  g := TImportLitLib.Shared;
  Check(f = g,                            "literal-vs-lib-value");
  Check(TImportLitLib.Double = g,         "imported-literal-left");
  Check(g = TImportLitLib.Double,         "imported-literal-right");
  Check(TImportLitLib.Double = TImportLitLib.Double,
                                          "two-imported-literals");
  Check(TImportLitLib.GetDouble() = f,    "getter-vs-literal");

  h := TImportLitLib.Double;
  Check(h(4) = 8,                         "anonymous-type-call");
  Check(h = f,                            "anonymous-vs-named");

  f := NIL;
  Check(f # TImportLitLib.Double,         "nil-vs-imported-literal")
END TImportLitUse.
