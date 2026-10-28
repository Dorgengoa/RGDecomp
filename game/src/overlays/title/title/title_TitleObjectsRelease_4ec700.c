/* rgp:protos */
#define RGP_SELF_title_TitleObjectsRelease_4ec700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EC700 -- a shutdown sweep.  Four `beql` guards whose
 * delay slots each carry the NEXT guard's load, which per the delay-slot rule
 * makes this an ordinary chain of independent `if`s, not an epilogue merge.
 * The fifth guard is a plain `beq` against -1 and skips a three-statement block.
 *
 * D_004803A0 is read for the guard and again for the argument, either side of
 * `func_1F59D0()`.  Plain, mwcc CSEs the two reads ACROSS THE CALL and parks
 * the value in $16, which costs the whole callee-saved frame -- 49 words with a
 * 0x20 prologue against retail's 47 with 0x10.  `volatile` is the anti-CSE
 * lever here exactly as it is the anti-hoist lever on a `const` extern; a plain
 * local for the guard does NOT break it (measured).
 */

extern void *D_00484150;
extern void *D_00484158;
extern void *D_00484160;
extern void *D_00484170;
extern s32 D_00484180;
extern volatile s32 D_004803A0;
extern u8 D_004803A4;
extern u8 D_004B2570;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleObjectsRelease_4ec700(void)
{
    if (D_00484170 != 0) {
        D_00484170 = 0;
    }
    if (D_00484160 != 0) {
        D_00484160 = 0;
    }
    if (D_00484158 != 0) {
        D_00484158 = 0;
    }
    if (D_00484150 != 0) {
        MemStackReset_14d830(D_00484150);
    }
    if (D_004803A0 != -1) {
        LoaderReleaseById_1cd340(GetLoaderMgr_1f59d0(), D_004803A0);
        D_004803A4 = 0;
        D_004803A0 = -1;
    }
    D_00484180 = 0;
    PadClearRepeatAll_183960((void *)&D_004B2570);
    PadClearStickDpadThreshold_183940((void *)&D_004B2570);
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
    return 1;
}
