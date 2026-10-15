#include "types.h"
/* insect 0x004F8260 -- 400 B / 100 words.  Carries the family guard verbatim
 * from src/wf/insect/insect_InsectSeqParseScript_4ea620.c:
 *     if (func_134BB0(NAME) < 0x10) { func_134A98(obj, NAME); }
 * with `extern u32 func_134BB0(const char *)` -- the UNSIGNED return is what
 * yields `sltiu $1,$2,0x10`, and the `beql` PAST the call makes the call the
 * fall-through, i.e. a plain positive `if`.  The run is
 * 14DB10 / 14DFF0 / 14D950+14D810 / 134BB0+134A98 / 14D830 / 14DAD0, the same
 * quartet 004ea620 and the already-matching 0050a9f0 use.
 * func_14DB10's return is DISCARDED here (read the $2 use per member).
 *
 * The dispatch is three `beql` INTO their arms -> SWITCH with the compare chain
 * REVERSED: retail tests 0xB, 0xA, 1, so the source order is 1, 10, 11 -- and
 * the arm bodies really are laid out 82AC / 8354 / 83B4 in that order.
 * The un-matched path is `b epilogue` with `ld $31` in the delay slot, i.e. no
 * default arm.
 *
 * !! MEASURED, build 1 (the unit's ONLY residue, 2 words): the case-10 `beql`
 * hoists `addiu $4,$16,0x5000` into its likely delay slot and .L004F8354 then
 * `jal insect_InsectFileSlotIsLoaded_512010` with a NOP delay -- so $4 is LIVE INTO that call
 * and insect_InsectFileSlotIsLoaded_512010 TAKES a->f5000.  Spelling it `()` gives `beq` + `nop`
 * and is exactly 2 words wrong.  A likely-branch whose delay slot carries an
 * argument register is an ARITY reading, not a scheduling accident.
 *
 * Frame proof: 3 sq'd callee-saved GPRs (0x30) + sd $31 at 0x30 -> 0x38,
 * rounded to 0x40, + ONE 4-byte local -> 0x44 -> 0x50, and the local sits at
 * the TOP of the frame (`addiu $5,$29,0x4C`).  So there is exactly one
 * address-taken local and nothing else on the stack.
 */

typedef struct Obj {
    u8    pad0000[0xDC];
    void *mDC;                          /* +0x00DC */
    u8    pad00E0[0x768 - 0xE0];
    u8    f768[1];                      /* +0x0768 */
    u8    pad0769[0x35F0 - 0x769];
    s32   m35F0;                        /* +0x35F0 */
    u8    pad35F4[0x5000 - 0x35F4];
    u8    f5000[1];                     /* +0x5000 */
} Obj;

extern const char D_00524CA8[];
extern const char D_00524CB0[];

extern s32   insect_InsectBattleGetStep_50d6a0(Obj *a, s32 b);
extern void  insect_InsectBattleSetStep_50d7a0(Obj *a, s32 b, s32 c, s32 d);
extern void  insect_InsectBattleSetState_50d8c0(Obj *a, s32 b, s32 c, s32 d);
extern s32   insect_InsectBattleTestFlag_50da40(Obj *a, s32 b);
extern void  insect_InsectFileSlotRequest_512140(void *p, const char *t, s32 n);
extern s32   insect_InsectFileSlotIsLoaded_512010(void *p);
extern void *insect_InsectFileSlotGetData_511fa0(void *p, s32 *out);
extern void  insect_InsectFileSlotRelease_512020(void *p);
extern s32   func_14DB10(void *h, s32 b, s32 c, s32 d);
extern void  func_14DFF0(void *o);
extern void *func_14D950(void *h, s32 n);
extern void  func_14D810(void *o, void *p, s32 n);
extern void  func_14D830(void *o);
extern void  func_14DAD0(void *h);
extern void  func_134A98(void *o, const char *t);
extern u32   func_134BB0(const char *t);
extern void  func_1BB6E0(s32 a);
extern s32   func_1B9F00(s32 a, void *b, void *c);

void insect_InsectBattleLoadSoundBank_4f8260(Obj *a)
{
    s32   tmp;
    void *h;
    void *o;
    void *r;

    switch (insect_InsectBattleGetStep_50d6a0(a, 1)) {
    case 1:
        insect_InsectFileSlotRequest_512140(a->f5000, D_00524CA8, 3);
        h = a->mDC;
        o = a->f768;
        func_14DB10(h, 2, 0, 0x40);
        func_14DFF0(o);
        func_14D810(o, func_14D950(h, 0x780), 0x780);
        if (func_134BB0(D_00524CB0) < 0x10) {
            func_134A98(o, D_00524CB0);
        }
        func_14D830(o);
        func_14DAD0(h);
        insect_InsectBattleSetStep_50d7a0(a, 10, 1, -1);
        break;
    case 10:
        if (insect_InsectFileSlotIsLoaded_512010(a->f5000) != 0) {
            r = insect_InsectFileSlotGetData_511fa0(a->f5000, &tmp);
            func_1BB6E0(5);
            a->m35F0 = func_1B9F00(5, r, a->f768);
            insect_InsectFileSlotRelease_512020(a->f5000);
            insect_InsectBattleSetStep_50d7a0(a, 11, 1, -1);
        }
        break;
    case 11:
        if (insect_InsectBattleTestFlag_50da40(a, 5) != 0) {
            insect_InsectBattleSetState_50d8c0(a, 0, 1, -1);
        }
        break;
    }
}
