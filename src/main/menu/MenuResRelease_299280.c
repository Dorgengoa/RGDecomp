#include "types.h"

extern void MenuModelRelease_2942c0(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableRemoveByName_158c40(s32, void *, s32);
extern s32 TexGroupClearAnim_157d10(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00461378[];
extern s32 D_00482338;
extern s32 D_00482410;

s32 MenuResRelease_299280(void)
{
    s32 t0;
    s32 r1;
    s32 r3;

    t0 = D_00482338;
    if (t0 != 0) {
        MenuModelRelease_2942c0();
    }
    r1 = GetDrawCtxNameTable_15de40();
    NameTableRemoveByName_158c40(r1, D_00461378, 0x32E);
    r3 = TexGroupClearAnim_157d10(r1, 0x32E);
    D_00482410 = 0;
    return 0;
}
