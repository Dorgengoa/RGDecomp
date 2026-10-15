#include "types.h"

/* factory.bin overlay, 0x004EAE00 -- the insect-cage twin of
 * `factory_FactoryBlueprintDialogSetStyle_4f7c70`: the same twelve cursor moves on widget 0x1A.
 *
 * ★★ THE TWO ARE NOT THE SAME SOURCE, AND THE DIFFERENCE IS THE GLOBAL.
 * 0x004F7C70 reloads D_004807E8 at all 24 sites, because each use is separated
 * by a call; this one reads D_004807E4 EXACTLY ONCE (`lw $16, -0x498C($28)` in
 * the guard's delay slot) and passes `daddu $4, $16, $0` at every site.  COUNT
 * THE LOADS: one load and a callee-saved register is a NAMED LOCAL, a load per
 * use is the global spelled out.  Writing either as the other is the right
 * length and the wrong bytes.
 *
 * ★ The load sits in the `beqz` delay slot, so it is read BEFORE the guard --
 * the local's assignment is the statement above the `if`.
 *
 * ★ `beqz $4, .L004EAF3C` branches AWAY on `on == 0`, so the source condition
 * is `on != 0` and the compact layout is the fall-through.
 *
 * ★ Cursor index 4 is absent from both arms, exactly as in 0x004F7C70.
 */

extern void *D_004807E4;

extern void func_28F970(void *ctx, s32 id, s32 x, s32 y, s32 n);

void factory_FactoryMenuBannerSetStyle_4eae00(s32 on)
{
    void *w;

    w = D_004807E4;
    if (on != 0) {
        func_28F970(w, 0x1A, 0x54, 0x4A, 0);
        func_28F970(w, 0x1A, 0x54, 0x5A, 1);
        func_28F970(w, 0x1A, 0x54, 0x66, 2);
        func_28F970(w, 0x1A, 0x38, 0x66, 3);
        func_28F970(w, 0x1A, 0x38, 0x4A, 5);
        func_28F970(w, 0x1A, 0x38, 0x5A, 6);
        func_28F970(w, 0x1A, 0x38, 0x66, 7);
        func_28F970(w, 0x1A, 0x48, 0x4A, 8);
        func_28F970(w, 0x1A, 0x48, 0x66, 9);
        func_28F970(w, 0x1A, 0x54, 0x4A, 0xA);
        func_28F970(w, 0x1A, 0x54, 0x5A, 0xB);
        func_28F970(w, 0x1A, 0x54, 0x66, 0xC);
    } else {
        func_28F970(w, 0x1A, 0x80, 0x4A, 0);
        func_28F970(w, 0x1A, 0x80, 0x5A, 1);
        func_28F970(w, 0x1A, 0x80, 0x66, 2);
        func_28F970(w, 0x1A, 0x64, 0x66, 3);
        func_28F970(w, 0x1A, 0x64, 0x4A, 5);
        func_28F970(w, 0x1A, 0x64, 0x5A, 6);
        func_28F970(w, 0x1A, 0x64, 0x66, 7);
        func_28F970(w, 0x1A, 0x74, 0x4A, 8);
        func_28F970(w, 0x1A, 0x74, 0x66, 9);
        func_28F970(w, 0x1A, 0x80, 0x4A, 0xA);
        func_28F970(w, 0x1A, 0x80, 0x5A, 0xB);
        func_28F970(w, 0x1A, 0x80, 0x66, 0xC);
    }
}
