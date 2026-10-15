#pragma opt_foldconstants off
/* ******* CLOSED s29 (2026-09-04) -- BYTE-IDENTICAL, 748 B, on ONE PRAGMA:
 *     #pragma opt_foldconstants off
 * (`opt_propagation off` gives the identical object.)  This was the image's
 * closest unit at ONE bad word since s21, with a stop verdict, an EMPTY corpus
 * oracle, and 15 measured source spellings on two different axes -- and the
 * recorded mechanism named the answer: "mwcc constant-folds `dy = -dy` because
 * `dy = 0x32` is the only definition reaching it".  The knob that turns that
 * fold off had never been swept on this unit.
 * !! The lesson is about SEARCH SHAPE, not this unit: s21 and s26 swept the
 * SOURCE axes the mechanism implicated and both concluded "unreachable from
 * C".  Both were right -- and the residue was reachable from the COMPILER.
 * Found by the WHOLE PRAGMA SURFACE, 6,592 arms (every lowercase identifier in
 * mwccps2.exe x 2 polarities + the numeric grammar), build/wf-normal/s29/
 * mkprag29.py + bulkmulti29.py, prag_fe2f0.log.  ARMED: 6,541 arms are the
 * identity object, 15 are live, and the optimization_level family gives four
 * distinct lengths, so the pragma line demonstrably reached the compiler
 * ([[mwcc-pragma-namespace]], [[probe-arming-proof]]). */
#include "types.h"
/* normal 0x004FE2F0 -- the world-map cursor's per-move refresh, the sibling of
 * normal_FUN_004FE750's open block.  When the cursor's row is unchanged but
 * its column moved it slides the 0x26/0x55/0x27/0x23 widgets by +-0x32, re-lays
 * the 0x25 ruler and fires 0x5603; then, exactly as 004FE750 does, it looks the
 * cell's entity up in D_00484454->f7C and hands it the 0x527B20 descriptor
 * through virtual slot 17 ((0x4C-8)/4).
 *
 * ONE VIRTUAL call (`lw $25,0($18) / lw $25,0x4C($25) / jalr $25`), so the unit
 * is .cpp -- a struct of function pointers gives `jalr $v0`.
 * `mult`/`mult1` is mwcc using BOTH EE multiplier pipes for the two independent
 * products of func_28DB40's third and fourth arguments -- one source statement.
 * `negu $16,$16` is `dy = -dy`, not a second constant.
 * `adda.s`/`madd.s` is plain `30.0f + (f32)p->f16 * D_004844B4`. */

/* SESSION 21: PARKED at ONE bad word, right length.  0x004FE394: retail
 * `negu $16,$16`, ours `addiu $16,$0,-50` -- mwcc constant-folds `dy = -dy`
 * because `dy = 0x32` is the only definition reaching it, and re-materialises
 * the constant instead of negating.  Length-neutral, so it is invisible to a
 * length guard.
 * MEASURED: SEVEN negate spellings give ONE OBJECT (fd02db9e) -- `-dy`,
 * `0 - dy`, `dy * -1`, `~dy + 1`, `-(dy)`, and `dy -= dy + dy` (a 2nd object,
 * still 1).  The ternary `dy = (p->f12 == 1) ? -0x32 : 0x32;` is 2 bad.
 * `dy = -*(volatile s32 *)&dy;` forces dy to a stack slot: +11 words.
 * Distinct spellings at an unchanged bad count is the signature of an
 * unreachable class (levers.d/insect-cse-two-spellings).
 * !! THE ORACLE IS EMPTY.  Across all 20,184 listings there are 70 self-negu
 * sites; only SIX are preceded within 3 instructions by `addiu $r,$0,K`, and
 * the only one with byte-identical C (InsectCageMarkerCompareByDist_388ea0) is a `-(bool)` --
 * `andi $2,$2,0xFF / negu $2,$2` -- not this shape.  The other four are
 * AngleDiffSign_13c0d0, MenuEquipCandidateCellCb_2b5960, TreasureBoxTrapApply_33a400 and normal_BtlChgMenuItemGridCursorMoveCb_4fdf70 (this
 * unit's own sibling, also open).  No compiled-C precedent to transfer.
 * The merged oracle instance for a REAL `negu` is insect_InsectFormationDecodeCell_4effa0, and
 * there the negated variable has TWO reaching definitions (`bias = 0;
 * if (..) bias = 1;`) so mwcc cannot fold -- that is the mechanism, and this
 * unit's `dy` has one.  build/wf-normal/s21/sw.py + v_fe2f0.py.
 * SESSION 26 -- s21's STOP VERDICT RE-TESTED ON THE AXIS IT NAMED BUT NEVER
 * SWEPT.  s21 measured seven spellings of the NEGATION; its own mechanism is
 * about the DEFINITION, so s26 swept the REACHING-DEFINITION SET instead:
 * `if(n<m) dy=0x32; else dy=0x32;`, a second def gated on `dir`,
 * `dy = dir ? 0x32 : 0x32;`, a self-assign before the negate, a self-assign in
 * the `else`, an `if/else` with both arms written out, `dy -= 2*dy`, and a
 * redundant `(s32)` on both sides.  EIGHT arms, and every one of them is the
 * SAME OBJECT fd02db9e that s21's seven negate spellings gave -- mwcc's
 * constant propagation runs before any of these shapes can matter.  Two more
 * (a def hoisted above the call, a second def gated on `dir`) are LENGTH-WRONG.
 * ⇒ The class is inert on BOTH axes now, not just the one s21 tested, and the
 * empty corpus oracle stands.  Do not re-open without a merged counter-example.
 * build/wf-normal/s26/v_fe2f0_def.py. */
typedef struct Mdl  { u8 pad00[0x30]; s32 f30; } Mdl;
typedef struct Slot { u8 pad00[4]; const void *f04; u8 pad08[0x14 - 8]; s32 f14; } Slot;
typedef struct Hold { u8 pad00[0x28]; Slot *f28; } Hold;

typedef struct Cur {
    u8  pad00[4];
    s16 f04;
    s16 f06;
    u8  pad08[0x10 - 8];
    s16 f10;
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Cur;

struct Ent {
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void attach(const void *p);    /* slot 17 -> vtable +0x4C */
    u8   pad04[0x10 - 4];
    Mdl *f10;
};

typedef struct Ctx { u8 pad00[0x7C]; Ent *f7C[1]; } Ctx;

extern const u8 D_005278E0[];
extern const u8 D_00527B20[];

extern "C" void *D_0048449C;      /* gp - 0xCD4  */
extern "C" void *D_00484498;      /* gp - 0xCD8  */
extern "C" Ctx  *D_00484454;      /* gp - 0xD1C  */
extern "C" f32   D_004844B4;      /* gp - 0xCBC  */
extern "C" s32   D_00480510;      /* gp - 0x4C60 */
extern "C" s32   D_00480514;      /* gp - 0x4C5C */
extern "C" s32   D_00480518;      /* gp - 0x4C58 */
extern "C" f32   D_0047D3F0;      /* gp - 0x7D80 */
extern "C" f32   D_0047D240;      /* gp - 0x7F30 */

extern "C" s32   func_1FEDE0(void);
extern "C" void  func_28DB40(const void *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h);
extern "C" void  func_28EDE0(void *p, s32 id, s32 a);
extern "C" Hold *func_290460(void *p, u16 id);
extern "C" void  func_290F50(void *p, u16 id, s32 x, s32 y, s32 c, f32 t);
extern "C" void  func_2910A0(void *p, u16 id, s32 *x, s32 *y);
extern "C" void  func_291110(void *p, u16 id, s32 c, s32 d);
extern "C" void  normal_BtlChgPageWeaponGridScrollRow_504410(Ctx *p, u16 id, s32 dir, s32 k);

extern "C" s32 normal_BtlChgMenuWeaponGridCursorMoveCb_4fe2f0(Cur *p);

s32 normal_BtlChgMenuWeaponGridCursorMoveCb_4fe2f0(Cur *p)
{
    s32   x0;
    s32   y0;
    s32   x1;
    s32   y1;
    s32   x2;
    s32   y2;
    s32   n;
    s32   m;
    s32   dir;
    s32   dy;
    s32   idx;
    s32   miss;
    Ent  *e;
    Ent **arr;
    Hold *w;
    Slot *sl;

    func_28DB40(D_005278E0, 0x28, p->f10 * p->f04 + 0x19, p->f12 * p->f06 + 0x17,
                0x2A, 0x30, 0x2B, 0xD1);
    if (p->f12 == D_00480514) {
        n = D_00480518;
        m = p->f16;
        if (m != n) {
            dir = 0;
            if (n < m) {
                dir = 1;
            }
            normal_BtlChgPageWeaponGridScrollRow_504410(D_00484454, 0x26, dir, m);
            dy = 0x32;
            if (p->f12 == 1) {
                dy = -dy;
            }
            func_2910A0(D_0048449C, 0x26, &x0, &y0);
            func_2910A0(D_0048449C, 0x27, &x1, &y1);
            func_2910A0(D_0048449C, 0x23, &x2, &y2);
            func_290F50(D_0048449C, 0x26, x0, y0 + dy, 0, D_0047D3F0);
            func_290F50(D_0048449C, 0x55, x0, y0 + dy, 0, D_0047D3F0);
            func_290F50(D_0048449C, 0x27, x1, y1 + dy, 0, D_0047D3F0);
            func_290F50(D_0048449C, 0x23, x2, y2 + dy, 0, D_0047D3F0);
            func_290F50(D_0048449C, 0x25, 0x183,
                        (s32)(30.0f + (f32)p->f16 * D_004844B4), 0, D_0047D240);
            func_28EDE0(D_00484498, 0x5603, 0);
        }
    }
    idx = (s16)(p->f10 + p->f12 * 8 + p->f16 * 8);
    arr = D_00484454->f7C;
    miss = 1;
    if (idx < 0xF0 && arr[idx] != 0) {
        if (func_1FEDE0() == 0) {
            return 0;
        }
        e = arr[idx];
        if (e == 0) {
            return 0;
        }
        w = func_290460(D_0048449C, 0x42);
        if (w == 0) {
            return 0;
        }
        sl = w->f28;
        if (sl == 0) {
            return 0;
        }
        e->attach(D_00527B20);
        sl->f04 = D_00527B20;
        sl->f14 = e->f10->f30;
        func_291110(D_0048449C, 0x41, 1, 1);
        miss = 0;
    }
    if (miss != 0) {
        func_291110(D_0048449C, 0x41, 0, 1);
    }
    D_00480510 = p->f10;
    D_00480514 = p->f12;
    D_00480518 = p->f16;
    return 1;
}
