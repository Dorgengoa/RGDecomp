/* === SESSION 72 (2026-09-21, SOLO): **MATCH**, merged, NORMAL.BIN relinked
 * BYTE-IDENTICAL with an armed 1-byte control at 0x005153B4.
 * s68's "wide armed null" on the argument-chain order was a TWO-EDIT CROSS,
 * and each half alone is inert:
 *   (a) NAME the two pointer chains, `SubX *sx = e2->f18;` FIRST and
 *       `SubB *sb = e2->f8;` second -- retail's EMISSION order, not the
 *       argument order;
 *   (b) `#pragma opt_dead_assignments off` at file scope.
 * With the chains inlined there is no assignment for the pass to keep, so the
 * pragma is byte-identical to base (that is why s68's 488-variant n_knob run
 * read it as inert); with the pragma on, propagation folds the names back onto
 * the deref temps and argument order wins (that is why s68's ~80 naming arms
 * were inert).  ARMED: sb-first/dassign_off = 4 bad, inline/dassign_off = 4,
 * bogus `opt_dead_assignmentS` = base, `opt_unroll_count off` fails to build.
 * ⚠ `#pragma opt_propagation off` -- the SAME pass on normal_TransSaveWriteTickCb_518c60 --
 * is 445 bad here at the right length; it is whole-function and this function
 * is 464 words.  dassign is the narrow one.  Sweeps build/wf-normal/s72/p*.py.
 * See [[levers.d/mwcc-opt-propagation-pragma]], [[levers.d/two-edit-cross-beats-count-ranking]].
 */
/* === SESSION 68 (2026-09-20, SOLO): 424 bad -> 4 BAD at EXACT LENGTH (464 w,
 * frame 0x70, 2 sq -- all three now match retail).  The unit was never a
 * spelling problem; it was SEVEN SOURCE DEFECTS, found by reading the retail
 * listing straight through.  Sweeps in build/wf-normal/s68/b*.py, c*.py.
 *
 *  1. SIGNATURE: `(s32 d1, void *arg1)` -- s67's argscan.py row, installed
 *     here.  Retail's first instruction is `beqz $5`.
 *  2. `D_004847A0 = 0;` belongs immediately BEFORE the 0x754C func_291110
 *     (retail schedules the `sh` into that jal's delay slot at 0x00515064).
 *     s31's automated DEFINING-STATEMENT MOVE deck had pushed it to the END
 *     of the arg1 block; the same deck made the same class of error on
 *     normal_TransMenuTopPickAnimStep_515550, which s68 closed by undoing it.
 *  3. `u8 sp40[0x24]`, not `[4]`.  Retail's locals run 0x40..0x6F; the 32-byte
 *     hole s67's note called "a missing local" is this buffer's real size.
 *  4. D_00484700 is used BY ADDRESS (`addiu $4,$28,-0xA70`), so it is
 *     `extern u8 D_00484700;` passed as `&D_00484700` -- NOT `extern void *`
 *     (that emits `lw`) and NOT `u8 D_00484700[]` (that emits lui+addiu).
 *     D_00484730 is read with `lbu`, so it is `u8`, not `s32`.
 *     D_005266C0 / D_005266E0 are the opposite case: they live in the
 *     OVERLAY's own data, retail spells them lui/addiu, so they must be
 *     `extern u8 D_xxxx[];` (array) and passed bare.
 *  5. `u8 ok = 1;` (was `s32 ok = 1 & 0xFF;`).  ** THE LOAD-BEARING EDIT:
 *     with `s32`, mwcc folds the mask and CSEs the literal 1 with the
 *     `id == 1` / `nav->f12 == 1` compare constant, which drags that constant
 *     into a THIRD callee-saved register.  `u8` forces retail's
 *     `andi $17,$6,0xFF` and lets `ok` re-use `id`'s register, exactly as
 *     retail does -- sq 3 -> 2 and -2 words.  ⚠ `s8`/`u16`/`s32`/`bool` do
 *     NOT do this; only `u8` (and `u8 ok; ok = 1;`).  Crossed with
 *     `if (ok)` in place of `if (ok != 0)`, which removes the read-back
 *     narrowing at the test (-1 more).
 *  6. `if ((D_00484730 != 0) && (nav->f12 < 2))` is ONE FLAT `&&`, not a
 *     nested `if`: retail's `beql` on D_00484730 jumps straight INTO the
 *     else block at 0x005152F4, and `which = nav->f12;` is duplicated into
 *     that beql's delay slot.  The 0/1 dispatch inside it must be an
 *     `if/else if`, not a `switch` (-1).  Same for `D_0048472C`: write the
 *     `!= 0` arm FIRST and the `a->f518 = 0.0f;` arm as the `else` (-1); the
 *     four other shapes are all +1.
 *  7. `s32 v16`, NOT `s16 v16` -- an `s16` local costs a whole extra
 *     dsll32/dsra32 pair on the read-back
 *     ([[levers.d/mwcc-readback-carries-conversion]]); retail's `lh $16` and
 *     `addiu $16,$0,-1` already leave the value sign-extended.
 *     Also `func_321E80(a, 15.0f)`, not 23.0f (0x41700000).
 *
 * ★ THE 4 LEFT ARE ONE SCHEDULER FACT, and the axis is a WIDE ARMED NULL.
 * At 0x005153AC retail evaluates the SECOND argument's pointer chain first:
 *     lw $3,0x18($2) / lw $2,0x8($2) / lh $5,0xF8($3) / lw $4,0x74($2)
 * we evaluate the first argument's chain first -- a perfect mirror, same
 * instruction count.  MEASURED NULL (~80 source arms, all one object):
 * a 7x7 cast grid on both arguments ({}, (s32), (u32), (long), (s16),
 * (s32)(u32), (s64)) is TWO objects and both are 4 bad; naming either or both
 * pointer chains in a local, naming either loaded VALUE, `[0]` / `(*p).`
 * / raw `*(T *)((u8*)p + off)` access forms, two separate view structs in
 * either declaration order, SubB-before-SubX, splitting the declarations,
 * putting the call in the `if` condition, and every prototype variant
 * (s8/s16/u16/s32/s64/varargs on either parameter).  `n_knob.py --all`:
 * 488 variants, 467 inert, 21 live, NONE below 4 -- the probe is armed
 * (schedule_off 0x84c, peephole_off 0x7d8, opt_common_subs_off 0x780).
 * ⚠ `s32 v16 = -1;` must stay BETWEEN `Ent *e2 = ...` and the call: moving it
 * either way is 0x73c, one word SHORT.
 * NEXT: this needs whatever decides mwcc's ARGUMENT-CHAIN creation order at a
 * two-pointer call -- allocator/scheduler level, not a spelling.
 * [[levers.d/mwcc-vreg-creation-source-position]], [[insect-session91-levers]].
 */
#include "types.h"
#pragma usefloatacc off
#pragma opt_dead_assignments off   /* s72: with the two pointer chains NAMED,
     * this pass is what preserves their DECLARATION order; sx (e2->f18) first is
     * retail's emission order.  `opt_propagation off` is the same pass elsewhere but
     * is 445 bad here.  Armed: sb-first/dassign_off and inline/dassign_off both 4. */

typedef struct SubX  { u8 pad00[0x30]; s16 f30; u8 pad32[0xF8 - 0x32]; s16 fF8; } SubX;
typedef struct SubB  { u8 pad00[0x74]; s32 f74; } SubB;
typedef struct Ent   { u8 pad00[8]; SubB *f8; u8 pad0C[0x18 - 0xC]; SubX *f18; } Ent;

typedef struct R10   { u8 pad00[8]; s16 f8; } R10;
typedef struct Res   { u8 pad00[0x10]; R10 *f10; u8 pad14[0x40 - 0x14]; s32 f40; } Res;

typedef struct Actor { u8 pad00[0x518]; f32 f518; } Actor;
typedef struct T12   { u8 pad00[0x12]; s16 f12; } T12;

extern const u8 D_004B2570[];
extern u8     D_00484700;          /* gp - 0xA70, used by ADDRESS (addiu $4,$28,-0xA70) */
extern void  *D_004846E8;          /* gp - 0xA88, widget handle */
extern void  *D_00484710;          /* gp - 0xA60, widget handle */
extern void  *D_0048478C;          /* gp - 0x9E4 */
extern f32    D_0047DA1C;          /* gp - 0x7754 */
extern s8     D_0048472C;          /* gp - 0xA44 */
extern f32    D_0047D344;          /* gp - 0x7E2C */
extern f32    D_0047DA0C;          /* gp - 0x7764 */
extern u8     D_00484730;          /* gp - 0xA40, read with lbu */
extern void  *D_00484770;          /* gp - 0xA00 */
extern s16    D_004847A4;          /* gp - 0x9CC */
extern s16    D_004847A0;          /* gp - 0x9D0 */
extern f32    D_0047D920;          /* gp - 0x7850 */
extern f32    D_0047D5D0;          /* gp - 0x7BA0 */
extern f32    D_0047DA20;          /* gp - 0x7750 */

extern u8     D_005266C0[];
extern u8     D_005266E0[];
extern T12    D_00527EE0;

extern Ent   *func_1FEDE0(void);
extern s32    func_1FEDF0(void);
extern s32    func_1DCB50(s32 a);
extern void   func_1E49B0(s32 a, s16 b, s32 *out);
extern void  *func_201A70(void);
extern s32    func_201A90(void);
extern void   func_206230(void);
extern void   func_206240(void);
extern s32    func_207F20(void);
extern void  *func_28AA30(void *a, s32 b);
extern void   func_28B160(void *a, s32 b);
extern void   func_28C120(void *a, void *b, s32 c);
extern s32    func_28E170(void *a, void *b, s32 c, s32 d);
extern T12   *func_28EC60(void *a);
extern void   func_28EDE0(void *a, s32 b, s32 c);
extern void   func_28F510(void *a, s32 b, void *c, s32 d);
extern void   func_28F670(void *a, u16 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void   func_2905B0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d);
extern void   func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern f32    func_290770(void *w, u16 id);
extern void   func_290F50(void *p, s32 id, s32 c, s32 d, s32 e, f32 x);
extern void   func_290F60(void *p, u16 id, s32 c, s32 d);
extern void   func_2910A0(void *p, u16 id, s32 *x, s32 *y);
extern void   func_291110(void *w, u16 id, s32 a, s32 b);
extern void   func_321A20(void *p, s32 a, s32 b);
extern void   func_321AC0(void *p, s32 a, s32 b);
extern void   func_321B60(void *p, s32 a, s32 b);
extern void   func_321C00(void *p, s32 a);
extern void   func_321E80(void *p, f32 a);
extern void   func_3F0960(s32 a, s32 b);
extern Res   *func_425590(s32 a, s16 b);
extern void   func_1343B8(void *a, void *b, s16 c);

extern void   normal_TransMenuTopPickAnimStep_515550(void);
extern void   normal_TransMenuPlayTimeSet_517310(s32 a);
extern void   normal_TransMenuLocationNameSet_5173c0(s32 a);
extern s32    normal_TransMenuSubResPoll_517d40(void);
extern void   normal_TransMenuSubResRequest_518040(s64 a);
extern s32    normal_TransMenuCanWarp_5185a0(void);
extern s32    normal_TransMenuIsHunterUnlocked_5185e0(void);

s32 normal_TransMenuTopState_514e10(s32 d1, void *arg1)
{
    s32   sp6C;
    s32   sp68;
    s32   sp64;
    u8    sp40[0x24];
    f32   spacing;
    s32   id;
    s32   i;
    s32   navId;
    T12  *nav;
    s16   navF12;
    s32   ret;

    if (arg1 != NULL) {
        Ent *e = func_1FEDE0();
        s32 handle = func_201A90();
        if (handle != 0) {
            sp6C = 0;
            func_1E49B0(handle, e->f18->f30, &sp6C);
            if ((sp6C != 0) && (func_1DCB50(sp6C) != 0)) {
                Actor *a = (Actor *)func_201A70();
                if (a != NULL) {
                    func_321C00(a, 1);
                    func_321B60(a, 0x10, 0x20);
                    func_321AC0(a, 0x1E0, 0x1E0);
                    func_321A20(a, 0x1E0, 0x180);
                    if (D_0048472C != 0) {
                        if (a->f518 < 1.0f) {
                            func_321E80(a, 15.0f);
                        }
                    } else {
                        a->f518 = 0.0f;
                    }
                }
            }
        }
        func_28B160(D_0048478C, 9);
        func_291110(D_004846E8, 0x7556, 1, 1);
        func_290690(D_004846E8, 0x7556, 1.0f, D_0047DA1C, 0.0f);
        func_28EA90(&D_00527EE0, 1, 0);
        i = 0;
        do {
            s32 base = (i * 0x26) + 0x4F;
            spacing = D_0047D344 - (D_0047DA0C * (f32)i);
            func_290F50(D_004846E8, (u16)(i + 0x753B), 0x21, base, 0, spacing);
            func_290F50(D_004846E8, (u16)(i + 0x7536), 0x24, base + 3, 0, spacing);
            func_291110(D_004846E8, (u16)(i + 0x753F), 1, 1);
            i++;
        } while (i < 4);
        nav = func_28EC60(&D_00527EE0);
        navF12 = nav->f12;
        id = (navF12 * 0x26) + 0x4F;
        func_290F50(D_004846E8, (u16)(navF12 + 0x753B), 0x2B, id, 0, D_0047D344);
        func_290F50(D_004846E8, (u16)(navF12 + 0x7536), 0x2E, id + 3, 0, D_0047D344);
        D_004847A0 = 0;
        func_291110(D_004846E8, 0x754C, 1, 1);
        func_291110(D_004846E8, 0x754B, 1, 1);
        func_2905B0(D_004846E8, 0x754B, 0.0f, 0.0f, 0.0f, D_0047D920);
        func_2910A0(D_004846E8, 0x754C, &sp68, &sp64);
        if (sp64 != 0x12) {
            func_290F60(D_004846E8, 0x754C, 0x9A, -0x28);
            func_290F60(D_004846E8, 0x754B, 0x9D, -0x25);
            func_290F50(D_004846E8, 0x754C, 0x9A, 0x12, 0, D_0047D5D0);
            func_290F50(D_004846E8, 0x754B, 0x9D, 0x15, 0, D_0047D5D0);
        }
        if (func_290770(D_004846E8, 0x75D1) < 1.0f) {
            func_290690(D_004846E8, 0x75D1, 1.0f, D_0047DA1C, -1.0f);
        }
        func_28C120(D_004846E8, D_005266C0, 0);
        normal_TransMenuLocationNameSet_5173c0(0x754E);
        if (func_207F20() == 0) {
            func_2905B0(D_00484710, 0x7541, 1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    id = func_28E170(&D_00527EE0, (void *)D_004B2570, 4, 0);
    nav = func_28EC60(&D_00527EE0);
    if (D_004847A0 == 0) {
        if (id == 1) {
            u8 ok = 1;
            if ((nav->f12 == 1) && (normal_TransMenuCanWarp_5185a0() == 0)) {
                ok = 0;
            }
            if ((nav->f12 == 2) && (normal_TransMenuIsHunterUnlocked_5185e0() == 0)) {
                ok = 0;
            }
            if ((func_207F20() != 0) && (nav->f12 != 1)) {
                ok = 0;
            }
            if (ok) {
                s16 which;
                func_1FEDE0();
                if ((D_00484730 != 0) && (nav->f12 < 2)) {
                    if (nav->f12 == 0) {
                        func_28F510(D_004846E8, 0x764E, func_28AA30(D_00484770, 0x7D0), 0);
                    } else if (nav->f12 == 1) {
                        func_28F510(D_004846E8, 0x764E, func_28AA30(D_00484770, 0x7D1), 0);
                    }
                    func_28EDE0(&D_00484700, 9, 0);
                } else {
                    which = nav->f12;
                    D_004847A4 = which;
                    func_1343B8(sp40, D_005266E0, which);
                    D_004847A0 = 1;
                    func_2905B0(D_004846E8, 0x7544, 1.0f, 1.0f, 1.0f, 1.0f);
                    func_290690(D_004846E8, 0x7556, 0.0f, D_0047DA20, -1.0f);
                    func_206230();
                    func_206240();
                    switch (nav->f12) {
                    case 0:
                        normal_TransMenuSubResRequest_518040(0);
                        break;
                    case 1: {
                        Ent *e2 = func_1FEDE0();
                        s32 v16 = -1;
                        SubX *sx = e2->f18;
                        SubB *sb = e2->f8;
                        Res *res = func_425590(sb->f74, sx->fF8);
                        if ((res != NULL) && (res->f40 & 1)) {
                            R10 *r10 = res->f10;
                            if (r10 != NULL) {
                                v16 = r10->f8;
                            }
                        }
                        normal_TransMenuSubResRequest_518040((s64)(s16)(v16 + 2));
                        break;
                    }
                    case 2:
                        func_3F0960(func_1FEDF0(), 2);
                        normal_TransMenuSubResRequest_518040(1);
                        break;
                    case 3:
                        normal_TransMenuSubResRequest_518040(1);
                        break;
                    }
                    func_28EA90(&D_00527EE0, 0x10, 0);
                }
            }
        } else if (id == 2) {
            func_28EDE0(&D_00484700, 4, 1);
        }
    }

    normal_TransMenuTopPickAnimStep_515550();
    normal_TransMenuPlayTimeSet_517310(0x754E);
    if ((D_004847A0 == 7) && (normal_TransMenuSubResPoll_517d40() != 0)) {
        D_004847A0 = 0;
        func_28F670(D_004846E8, (u16)(D_004847A4 + 0x753B), 0x76, 0x1B, 4, 4, 0);
        switch (D_004847A4) {
        case 0:
            func_28EDE0(&D_00484700, 5, 1);
            break;
        case 1:
            func_28EDE0(&D_00484700, 0xB, 1);
            break;
        case 2:
            func_28EDE0(&D_00484700, 0x10, 1);
            break;
        case 3:
            func_28EDE0(&D_00484700, 0x1F, 1);
            break;
        }
    }
    return 1;
}
