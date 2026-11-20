/*
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright (c) 2026 nemavasi
 */

/** Проба ADR-309: копирование короткого массива в фиксированный. */
public final class TCopyMain {

    public static void main(String[] a) {
        CP.TCopy.TCopy_Rec src = new CP.TCopy.TCopy_Rec();
        CP.TCopy.TCopy_Rec dst = new CP.TCopy.TCopy_Rec();
        src.label = "Step".toCharArray();     // 4 символа, без 0X
        CP.TCopy.TCopy.CopyInto(dst, src);
        boolean ok = dst.label[0] == 'S' && dst.label[1] == 't'
                && dst.label[2] == 'e' && dst.label[3] == 'p'
                && dst.label[4] == 0;
        System.out.println(ok ? "PASS" : "FAIL");
        Runtime.getRuntime().halt(ok ? 0 : 1);
    }

    private TCopyMain() {
    }
}
