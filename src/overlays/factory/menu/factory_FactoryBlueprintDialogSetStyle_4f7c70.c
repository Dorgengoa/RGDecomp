#include "types.h"

/* factory.bin overlay, 0x004F7C70 -- move the twelve blueprint-grid cursors of
 * widget 0x92 between the compact and the expanded layout.
 *
 * ★ THE FIRST PARAMETER IS UNUSED HERE AND THE FUNCTION STILL TAKES TWO.  The
 * body never reads $4 -- it loads D_004807E8 itself -- but both call sites at
 * 0x004F8E5x marshal it with `daddu $4, $20, $0`, and dropping it from the
 * prototype costs `factory_FactoryBlueprintCancel_4fb5a0` a word in a different function
 * entirely (see that file).  An unused parameter is invisible from inside the
 * callee; the CALLERS are the evidence.
 *
 * ★ `beqz $5, .L004F7DA4` branches AWAY on `on == 0` and falls through into
 * the expanded layout, so the source condition is `on != 0` -- guard polarity
 * read off the branch, not off m2c.
 *
 * ★ Cursor index 4 is absent from both arms; the ids run 0..3, 5..9, 0xA..0xC.
 *
 * ★ D_004807E8 is read at every one of the 24 sites and retail reloads it at
 * each, because each use is separated by a call -- mwcc's per-basic-block CSE
 * reproduces that from the plain source.  Do NOT hoist it into a local.
 */

extern void *D_004807E8;

extern void func_28F970(void *ctx, s32 id, s32 x, s32 y, s32 n);

void factory_FactoryBlueprintDialogSetStyle_4f7c70(void *o, s32 on)
{
    if (on != 0) {
        func_28F970(D_004807E8, 0x92, 0x54, 0x4A, 0);
        func_28F970(D_004807E8, 0x92, 0x54, 0x5A, 1);
        func_28F970(D_004807E8, 0x92, 0x54, 0x66, 2);
        func_28F970(D_004807E8, 0x92, 0x38, 0x66, 3);
        func_28F970(D_004807E8, 0x92, 0x38, 0x4A, 5);
        func_28F970(D_004807E8, 0x92, 0x38, 0x5A, 6);
        func_28F970(D_004807E8, 0x92, 0x38, 0x66, 7);
        func_28F970(D_004807E8, 0x92, 0x48, 0x4A, 8);
        func_28F970(D_004807E8, 0x92, 0x48, 0x66, 9);
        func_28F970(D_004807E8, 0x92, 0x54, 0x4A, 0xA);
        func_28F970(D_004807E8, 0x92, 0x54, 0x5A, 0xB);
        func_28F970(D_004807E8, 0x92, 0x54, 0x66, 0xC);
    } else {
        func_28F970(D_004807E8, 0x92, 0x80, 0x4A, 0);
        func_28F970(D_004807E8, 0x92, 0x80, 0x5A, 1);
        func_28F970(D_004807E8, 0x92, 0x80, 0x66, 2);
        func_28F970(D_004807E8, 0x92, 0x64, 0x66, 3);
        func_28F970(D_004807E8, 0x92, 0x64, 0x4A, 5);
        func_28F970(D_004807E8, 0x92, 0x64, 0x5A, 6);
        func_28F970(D_004807E8, 0x92, 0x64, 0x66, 7);
        func_28F970(D_004807E8, 0x92, 0x74, 0x4A, 8);
        func_28F970(D_004807E8, 0x92, 0x74, 0x66, 9);
        func_28F970(D_004807E8, 0x92, 0x80, 0x4A, 0xA);
        func_28F970(D_004807E8, 0x92, 0x80, 0x5A, 0xB);
        func_28F970(D_004807E8, 0x92, 0x80, 0x66, 0xC);
    }
}
