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

(* ADR-012: ARRAY OF SHORTCHAR must be allocated as char[], not short[]. *)
MODULE TShortChar;
  IMPORT CPmain, Console;
  TYPE Buf = ARRAY 4 OF SHORTCHAR;
  VAR g: Buf;
  PROCEDURE Fill(VAR x: ARRAY OF SHORTCHAR; OUT n: INTEGER);
    VAR i: INTEGER;
  BEGIN
    n := LEN(x);
    FOR i := 0 TO LEN(x) - 1 DO x[i] := SHORT(CHR(ORD("A") + i)) END
  END Fill;
  PROCEDURE Run;
    VAR l: Buf; n: INTEGER;
  BEGIN
    Fill(l, n);
    g[0] := 41X; g[1] := 42X;
    IF (n = 4) & (l[0] = 41X) & (l[3] = 44X) &
       (g[0] = 41X) & (g[1] = 42X) THEN
      Console.WriteString("PASS")
    ELSE
      Console.WriteString("FAIL")
    END;
    Console.WriteLn()
  END Run;
BEGIN Run END TShortChar.
