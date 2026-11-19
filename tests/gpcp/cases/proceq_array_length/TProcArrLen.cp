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

MODULE TProcArrLen;
  IMPORT CPmain;
  TYPE Arr4 = ARRAY 4 OF INTEGER; Arr8 = ARRAY 8 OF INTEGER;
       H4 = PROCEDURE (a: Arr4): INTEGER;
       H8 = PROCEDURE (a: Arr8): INTEGER;
       HO = PROCEDURE (a: ARRAY OF INTEGER): INTEGER;
  VAR f4: H4; f8: H8; fo: HO;
      a4: Arr4; a8: Arr8;
  PROCEDURE P4(a: Arr4): INTEGER; BEGIN RETURN a[0] END P4;
  PROCEDURE P8(a: Arr8): INTEGER; BEGIN RETURN a[0] END P8;
  PROCEDURE PO(a: ARRAY OF INTEGER): INTEGER; BEGIN RETURN LEN(a) END PO;
BEGIN
  a4[0] := 4; a8[0] := 8;
  f4 := P4; f8 := P8; fo := PO;
  ASSERT(f4(a4) = 4); ASSERT(f8(a8) = 8); ASSERT(fo(a8) = 8)
END TProcArrLen.
