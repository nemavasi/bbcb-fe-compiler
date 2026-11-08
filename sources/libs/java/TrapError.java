/*
New BSD License (BSD)
Copyright (c) 2026, nemavasi

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

* Neither my name may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/** Trap thrown by HALT and by compiler-generated trap sites.
 *
 *  Semantics follow BlackBox 1.7.2: a trap aborts the current command,
 *  it is not an ordinary exception (it is not caught by CP RESCUE/TRY).
 */

package CP.CPJrts;

public final class TrapError extends Error
{
    /** ASSERT(x) without a code traps 0, like BlackBox AssertTrap = 0. */
    public static final int ASSERT = 0;
    public static final int WITH = 129;
    public static final int CASE = 130;
    public static final int INVARIANT = 100;

    public final int code;
    public final String text;

    /* C3 (optional): snapshot of locals at the trap site; may be null. */
    public final String[] names;
    public final Object[] values;

    public TrapError(int code)
    {
        this(code, "TRAP " + code);
    }

    public TrapError(int code, String text)
    {
        this(code, text, null, null);
    }

    public TrapError(int code, String text, String[] names, Object[] values)
    {
        super(text);
        this.code = code;
        this.text = text;
        this.names = names;
        this.values = values;
    }

    /** Parse the code out of the message produced by JavaMaker. */
    public TrapError(String msg)
    {
        this(parseCode(msg), msg);
    }

    private static int parseCode(String m)
    {
        if (m == null) return INVARIANT;
        if (m.startsWith("Assertion failure ")) {
            String rest = m.substring("Assertion failure ".length()).trim();
            int n = rest.length();
            for (int i = 0; i < n; i++)
                if (!Character.isDigit(rest.charAt(i))) return ASSERT;
            try { return Integer.parseInt(rest); }
            catch (NumberFormatException e) { return ASSERT; }
        }
        if (m.startsWith("CASE-trap:")) return CASE;
        if (m.startsWith("WITH else-trap:")) return WITH;
        return INVARIANT;
    }

    @Override
    public String toString()
    {
        return "CP.CPJrts.TrapError: TRAP " + code + " [" + getMessage() + "]";
    }
}