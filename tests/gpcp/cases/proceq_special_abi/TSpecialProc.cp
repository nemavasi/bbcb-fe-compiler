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

(* fixProcEqual ABI: procedure values cross the boundary into a native
   (-special) module.  The generated Proc$Lit$ wrappers must extend the
   named Java host class expected by the hand-written body. *)
MODULE TSpecialProc;
  IMPORT CPmain, Console, SpecialProc;

  VAR
    h: SpecialProc.Handler;
    c: SpecialProc.Command;

  PROCEDURE H(x: INTEGER);
  BEGIN Console.WriteInt(x, 0) END H;

  PROCEDURE C(x: INTEGER);
  BEGIN Console.WriteInt(x, 0) END C;

BEGIN
  h := H;
  c := C;
  SpecialProc.Install(h);
  SpecialProc.Run(c);
  IF h = h THEN Console.WriteString(" eq") END;
  IF h # c THEN Console.WriteString(" ne") END;
 (* Handler and Command are distinct -special host classes with the same
    signature; both wrappers implement ProcKey, so the same procedure
    compares equal across them. *)
  c := H;
  IF h = c THEN Console.WriteString(" cross") END;
  Console.WriteLn()
END TSpecialProc.