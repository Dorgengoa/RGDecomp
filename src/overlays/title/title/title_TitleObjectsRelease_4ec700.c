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
extern const u8 D_004B2570;

extern void func_14D830(void *a);
extern void *func_1F59D0(void);
extern void func_1CD340(void *a, s32 b);
extern void func_183960(void *a);
extern void func_183940(void *a);
extern void *func_206A40(void);
extern void func_42B650(void *a, s32 b);

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
        func_14D830(D_00484150);
    }
    if (D_004803A0 != -1) {
        func_1CD340(func_1F59D0(), D_004803A0);
        D_004803A4 = 0;
        D_004803A0 = -1;
    }
    D_00484180 = 0;
    func_183960((void *)&D_004B2570);
    func_183940((void *)&D_004B2570);
    func_42B650(func_206A40(), 2);
    return 1;
}
