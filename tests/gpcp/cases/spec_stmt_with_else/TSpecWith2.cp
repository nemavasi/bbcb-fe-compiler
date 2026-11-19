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

MODULE TSpecWith2;
  IMPORT CPmain;
  TYPE Base = EXTENSIBLE RECORD x: INTEGER END;
       A = RECORD (Base) a: INTEGER END;
       B = RECORD (Base) b: INTEGER END;
       PBase = POINTER TO Base; PA = POINTER TO A; PB = POINTER TO B;
  VAR p: PBase; a: PA; b: PB; y: INTEGER;
BEGIN
  NEW(a); a.x := 1; a.a := 2; p := a;
  WITH p: PA DO y := p.a | p: PB DO y := p.b ELSE y := 0 END;
  ASSERT(y = 2);
  NEW(b); b.x := 3; b.b := 4; p := b;
  WITH p: PA DO y := p.a ELSE y := 9 END;
  ASSERT(y = 9)
END TSpecWith2.
