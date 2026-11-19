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

(* fixProcEqual regression: only procedure-typed comparisons may change.
   Pointer, string, CHAR, integer, REAL and SET comparisons keep their
   existing semantics. *)
MODULE TProcEqCmp;
  IMPORT CPmain, Console;

  TYPE
    P = POINTER TO RECORD x: INTEGER END;

  VAR
    ok: BOOLEAN;
    p, q: P;
    s, t: ARRAY 8 OF CHAR;
    i, j: INTEGER;
    r: REAL;
    set: SET;

BEGIN
  NEW(p); q := p; NEW(p);
  s := 'abc'; t := 'abc';
  i := 7; j := 7; r := 1.5; set := {1,2};

  ok := (p # q) & (q = q) & (p # NIL) &
        (s = t) & (s # 'abd') &
        ("A" = "A") & ("A" # "B") &
        (i = j) & (i # 8) &
        (r = 1.5) &
        (set = {1,2});

  IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TProcEqCmp.
