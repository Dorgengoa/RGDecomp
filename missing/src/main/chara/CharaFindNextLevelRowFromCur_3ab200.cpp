/* rg-missing: CharaFindNextLevelRowFromCur_3ab200 (retail MAIN 0x003AB200, size 0x14)
 * why: Chara vtable slot (between CharaFindNextLevelRow_3ac830 and
 * CharaNextLevelRowLevel_3ac7f0) in the six Chara vtables D_004722A0..D_00473BF0;
 * the snapshot has no C, and its data names the entry func_003AB200.
 * retail: lw $25,0($4); lhu $5,0x10($4); lw $25,0x434($25); jr $25
 *   = return this->CharaFindNextLevelRow_3ac830-slot(0x434)(this, (u16 at +0x10)).
 * Checked: mwcc 3.0.1b210 -O4 (C++) compiles this body to retail's 4 words (MATCH). */
#include "types.h"

#ifdef __MWERKS__
#include "vshim_charalv.h" /* out/missing-staged/verify: placeholder virtuals, slot 0x434 */
#define CHARA_V434(o, a) (((VCharaLv *)(o))->FindLevelRow(a))
#else
#define CHARA_V434(o, a) VCALL(o, 0, 0x434, s32, (void *, s32), a)
#endif

extern "C" s32 CharaFindNextLevelRowFromCur_3ab200(void *o)
{
    return CHARA_V434(o, *(u16 *)((u8 *)o + 0x10));
}

#ifndef __MWERKS__
/* the snapshot's data (Chara vtables) and missing/UNBOUND.tsv spell this entry func_003AB200 */
extern "C" s32 func_003AB200(void *o)
{
    return CharaFindNextLevelRowFromCur_3ab200(o);
}
#endif
