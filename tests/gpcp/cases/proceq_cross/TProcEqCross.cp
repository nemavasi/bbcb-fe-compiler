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

(* fixProcEqual: values produced in one module must compare structurally
   with values of the same procedure produced elsewhere.  Two procedures
   with the same name and signature but different owners are not equal. *)
MODULE TProcEqCross;
  IMPORT CPmain, Console, TProcEqLib;

  VAR
    f, g: TProcEqLib.Hook;

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
  f := TProcEqLib.Shared;
  g := TProcEqLib.GetDouble();
  Check(f = g,                       "lib-shared-vs-getter");
  Check(g = TProcEqLib.GetDouble(),  "two-getter-calls");
  Check(f = TProcEqLib.GetDouble(),  "shared-vs-getter");

  TProcEqLib.Store(Double);
  Check(TProcEqLib.Get() = Double,   "lib-stored-vs-fresh-literal");
  Check(Double = TProcEqLib.Get(),   "fresh-literal-vs-lib-stored");
  Check(TProcEqLib.Same(TProcEqLib.Get(), Double),
                                     "lib-compare-stored-vs-literal");
  Check(TProcEqLib.Same(TProcEqLib.Get(), TProcEqLib.Get()),
                                     "lib-compare-stored-vs-stored");

  Check(~TProcEqLib.Same(TProcEqLib.GetDouble(), Double),
                                     "same-name-different-owner");

  TProcEqLib.Store(NIL);
  Check(TProcEqLib.Get() = NIL,      "lib-stored-nil");
  Check(~TProcEqLib.Same(TProcEqLib.Get(), Double),
                                     "lib-compare-nil-vs-literal")
END TProcEqCross.
