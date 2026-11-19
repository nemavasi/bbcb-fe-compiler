package CP.TProcIdent;

public class Probe {
    public static void main(String[] args) {
        Object f = TProcIdent.f;
        Object g = TProcIdent.g;
        if (!f.equals(g)) { System.out.println("FAIL equals"); return; }
        if (f.hashCode() != g.hashCode()) {
            System.out.println("FAIL hashCode"); return;
        }
        try {
            CP.CPJrts.ProcKey.class.getMethod("procEnv");
            System.out.println("FAIL procEnv interface"); return;
        } catch (NoSuchMethodException expected) { }
        try {
            f.getClass().getMethod("procEnv");
            System.out.println("FAIL procEnv wrapper"); return;
        } catch (NoSuchMethodException expected) { }
        Class<?> c4 = TProcIdent.h4.getClass().getSuperclass();
        Class<?> c8 = TProcIdent.h8.getClass().getSuperclass();
        Class<?> co = TProcIdent.ho.getClass().getSuperclass();
        if (c4 == c8) { System.out.println("FAIL fixed-length host"); return; }
        if (c4 == co || c8 == co) {
            System.out.println("FAIL open/fixed host"); return;
        }
        System.out.println("PASS");
    }
}
