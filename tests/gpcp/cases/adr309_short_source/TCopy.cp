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

(* ADR-309: the JVM back end must copy MIN(declared length, source length)
   elements into a fixed-size array.  A `$` string value is a char[] of
   exactly the string length; the old code took the declared 256 and read past
   the end of the source ("Index 255 out of bounds for length 4", hit while
   loading the original Dev/Rsrc/RTDebug form).  The probe replaces a record
   field with a short char[] (Java does not check CP types), so the emitted
   copy loop is what is being tested. *)
MODULE TCopy;
  IMPORT CPmain;

  TYPE Rec* = RECORD label*: ARRAY 256 OF CHAR END;

  PROCEDURE CopyInto* (VAR dst, src: Rec);
  BEGIN
    dst.label := src.label
  END CopyInto;

BEGIN
END TCopy.
