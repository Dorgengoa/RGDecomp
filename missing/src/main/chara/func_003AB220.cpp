/* rg-missing: func_003AB220 (retail MAIN 0x003AB220, size 0x14; no retail name)
 * why: Chara vtable slot after CharaNextLevelExp_3ac780 in the six Chara vtables
 * D_004722A0..D_00473BF0; the snapshot has no C.
 * retail: lw $25,0($4); lhu $5,0x10($4); lw $25,0x444($25); jr $25
 *   = return this->CharaNextLevelExp_3ac780-slot(0x444)(this, (u16 at +0x10));
 *   reads as "CharaNextLevelExpFromCur" (the 3ab200 twin).
 * Checked: mwcc 3.0.1b210 -O4 (C++) compiles this body to retail's 4 words (MATCH). */
#include "types.h"

#ifdef __MWERKS__
#include "vshim_charalv.h" /* out/missing-staged/verify: placeholder virtuals, slot 0x444 */
#define CHARA_V444(o, a) (((VCharaLv *)(o))->LevelExp(a))
#else
#define CHARA_V444(o, a) VCALL(o, 0, 0x444, s32, (void *, s32), a)
#endif

extern "C" s32 func_003AB220(void *o)
{
    return CHARA_V444(o, *(u16 *)((u8 *)o + 0x10));
}
