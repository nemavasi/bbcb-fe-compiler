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
    public static final int OVERFLOW = 138;
    public static final int DIV_ZERO = 139;
    public static final int STRING_TOO_LONG = 136;
    public static final int RANGE = 134;
    public static final int REAL_INF = 140;
    public static final int REAL_UNDERFLOW = 141;
    public static final int REAL_OVERFLOW = 142;
    public static final int REAL_UNDEFINED = 143;

    public final int code;
    public final String text;

    /* C3: snapshot of locals at the trap site; may be null. */
    public final String[] names;
    public final Object[] values;

    /* Original exception for a compiler catch-all (runtime trap); may be null. */
    public final Throwable cause;

    /* Method whose catch-all produced names/values (null => top frame). */
    public final StackTraceElement snapshotAt;

    /* Full Java stack trace captured when the trap object was constructed. */
    public final StackTraceElement[] javaTrace;

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
        this(code, text, names, values, null);
    }

    /** Trap for a compiler catch-all: keep the original exception's stack. */
    public TrapError(int code, String text, String[] names, Object[] values,
                     Throwable cause)
    {
        this(code, text, names, values, cause, null);
    }

    public TrapError(int code, String text, String[] names, Object[] values,
                     Throwable cause, StackTraceElement snapshotAt)
    {
        super(text);
        this.code = code;
        this.text = text;
        this.names = names;
        this.values = values;
        this.cause = cause;
        this.snapshotAt = snapshotAt;
        this.javaTrace = cause != null ? cause.getStackTrace() : getStackTrace();
        if (cause != null) {
            try { initCause(cause); } catch (Throwable ignored) { }
        }
    }

    /** Parse the code out of the message produced by JavaMaker. */
    public TrapError(String msg)
    {
        this(parseCode(msg), msg);
    }

    public TrapError(String msg, String[] names, Object[] values)
    {
        this(parseCode(msg), msg, names, values);
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
        int n = codeFromText(m);
        return n >= 0 ? n : INVARIANT;
    }

    /** Код из текста BlackBox: `TRAP 131`, `#143: ...`, `ASSERT 20: ...`. */
    private static int codeFromText(String m)
    {
        String s = m.trim();
        if (s.startsWith("TRAP ")) return digits(s, 5);
        if (s.startsWith("#")) return digits(s, 1);
        if (s.startsWith("ASSERT")) {
            int i = 6;
            while (i < s.length() && Character.isWhitespace(s.charAt(i))) i++;
            int n = digits(s, i);
            return n < 0 ? ASSERT : n;
        }
        return -1;
    }

    /** Число, начинающееся с позиции `i`, либо -1. */
    private static int digits(String s, int i)
    {
        int j = i;
        int n = 0;
        while (j < s.length() && Character.isDigit(s.charAt(j))) {
            n = n * 10 + (s.charAt(j) - '0');
            j++;
        }
        return j > i ? n : -1;
    }

    /** Render the complete Java stack trace captured at the trap site. */
    public String javaTraceText()
    {
        StringBuilder b = new StringBuilder();
        if (javaTrace != null) {
            for (StackTraceElement e : javaTrace) {
                b.append("    at ").append(e).append('\n');
            }
        }
        return b.toString();
    }

    @Override
    public String toString()
    {
        StringBuilder b = new StringBuilder();
        b.append("CP.CPJrts.TrapError: TRAP ").append(code)
         .append(" [").append(getMessage()).append("]");
        if (names != null) {
            b.append(" locals=");
            for (int i = 0; i < names.length; i++) {
                if (i != 0) b.append(',');
                b.append(names[i]);
            }
        }
        b.append('\n').append(javaTraceText());
        return b.toString();
    }
}