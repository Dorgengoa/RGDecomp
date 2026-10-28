/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyQtyState_50d1b0 1
#include "port/game_protos.h"
#line 1
/* === SESSION 71 (2026-09-21, SOLO): 108 bad -> MATCH.  Read against the
 * listing (build/wf-normal/s71/k1..k4.py):
 *  - `func_3C6460(ctx->f18, ..., qty, ...) == 0` -> D_00484630 = 2 arm FIRST
 *    (retail's fall-through), the 0x753B arm second.
 *  - the x dispatch is `if (!(x != 1 && x != 2)) { if (x == 1) {..} else if
 *    (x == 2) {..}  <common block> }` -- ONE outer guard; the two separate
 *    compares need the De Morgan spelling ([[normal-session68-levers]]).
 *  - ★ func_3C6460's THIRD PARAMETER IS s16.  Retail narrows qty once into
 *    $a2 for the multiply and passes that same register; an s16 prototype
 *    makes the call-site narrowing CSE with the multiply's.  This one edit
 *    ALSO dissolved s56's "whole-function callee-saved permutation" -- the
 *    extra `move a2,s3` had been costing a register.  (Passing `(s16)qty`
 *    instead folds BOTH narrowings away.)
 *  - first block `lim = ...; qty = pnl->f10;` in that order; second block
 *    reads `pnl->f10` inline in the compare (retail re-loads after the call).
 * Everything below predates this session. */
/* SESSION 65: `(s16)q >= 100` -> `> 99`, the [[at-compare-class]] operator
 * spelling for retail's `slti $1,$3,0x64`.  atscan.py's `slti_at: 1->0` row is
 * gone; one `sltiu_at: 0->1` row remains (we put a sltiu in $at where retail
 * uses a GPR -- the OPPOSITE direction).  Still 108 bad / 225 words.
 */
/* SESSION 56 (2026-09-15, SOLO): NO MOVE, 108 bad / 225 words.  s19's header
 * says "1 arm tried: a full declaration reorder ... the current declaration
 * order IS that arm" -- i.e. the only prior test was a NO-OP.  Ran a genuinely
 * different one: retail's map is w=$s6, pnl=$s3, ctx=$s2, st=$s0 (read off the
 * listing at 0x0050D1F0-0x0050D218; none of the three are declared adjacently
 * in the current source, which is scattered `st, m, ctx, pnl, t, qty, w, ...`).
 * Declared the four CONTIGUOUSLY as `w, pnl, ctx, st, m, t, qty, ...` (the
 * order that would produce retail's map under the plain "later decl -> lower
 * register" rule, since w needs the highest of the four registers and st the
 * lowest). Result: BYTE-IDENTICAL to baseline object, confirmed by hash, not
 * just by bad-count -- so the earlier "declaration position alone is inert"
 * verdict is now doubly measured (a trivial no-op AND a real contiguous
 * reorder), not resting on the accidental no-op alone.  This is
 * [[levers.d/mwcc-gpr-decl-order-map]]'s "companion trap" shape (NORMAL
 * 00513000, same file): the axis reads inert when a LIVE RANGE is wrong, not
 * when order is wrong.  NEXT: look for an argument or read that could be
 * routed through the WRONG one of {w, pnl, ctx, st} the way 00513000's
 * `func_3ED680(arg0, ...)` should have been `func_3ED680(ent, ...)` -- a
 * live-range fix, not another decl-order sweep.  Reverted clean. */
/* ===== LANE nd, session 19 -- 5 words SHORT -> RIGHT LENGTH (225), 108 bad.
 * LEVER: the three `dsll32/dsra32 ..,16` pairs are an explicit `(s16)`
 * RE-NARROW of an s32 local AT ITS USE ([[normal-s16-cast-sign-extension]]):
 *   `if (lim < (s16)qty * func_3CE6E0(...))`   (0x0050D26C)
 *   `if ((s16)q >= 100)` / `if (pnl->f08 < (s16)q)` / `if ((s16)q <= 0)`
 * and, the other way, `s32 w` not `s16 w` kills the widening retail does NOT
 * have at the closing `if (w != pnl->f10)` (0x0050D4F8).  Worth 5 words --
 * this closed the LENGTH.
 * MEASURED NULL (1 arm): a full callee-saved DECLARATION REORDER to retail's
 * register map ($16=st $17=m $18=ctx $19=pnl $20=t $21=qty $22=w) is
 * BYTE-IDENTICAL INERT -- 108 bad words at the SAME 108 addresses before and
 * after.  Corroborates overlay-normal's "declaration POSITION alone is inert
 * for callee-saved RANKING".  The current declaration order IS that arm.
 * RESIDUE: a callee-saved register PERMUTATION (ours $18 where retail has $19
 * at 0x0050D1FC, ours $19 where retail has $16 at 0x0050D214, ...).  Next lead
 * is an assignment-PLACEMENT sweep, not another declaration sweep.
 * 3 round trips spent. */
#include "types.h"
/* ⚠ PARKED at 5 words short (len 0x370 vs retail 0x384), tag gr1x1.
 * All 26 jal sites match retail 1:1 (verified by count) and the shape through
 * the m==NULL guard is proven correct (identical to the already-MERGED sibling
 * normal_ShopMenuBuyQtyCursorMoveCb_50cf50 -- same PM/PO/PS/PR/PC types, same func_3CE6E0/
 * func_3C6460/normal_ShopMenuBuyTotalPriceSet_50bb00 tail).  Residue is somewhere past that point
 * -- the st==1/st==2 dispatch, the D_004845D0->f14 +-10 clamp, or the shared
 * final `if (w != pnl->f10) func_289EF0(4);` tail -- but the build tool can't
 * emit a per-instruction diff while lengths differ, so the exact address is
 * unknown.  ARM TRIED: nesting the +-10 clamp inside `if (x==1||x==2) { if
 * (x==1) {...} else {...} ... }` instead of two flat `if`s made it WORSE
 * (8 words short, 0x364) -- mwcc collapsed a comparison the flat form kept.
 * Do not re-try that nesting.  Next lead: the [[normal-cse-cost-split]] /
 * [[at-compare-class]] levers on the st==1 dispatch, or check whether the
 * `t = 0; if (o->f14>=0) t=o->f14;` idiom should be a ternary (lever 1). */
/* normal 0x0050D1B0 -- shop quantity-picker step, sibling of
 * normal_ShopMenuBuyQtyCursorMoveCb_50cf50 (same D_004845CC/0x4F widget group, same
 * PM/PO/PS/PR/PC shapes, same func_3CE6E0/func_3C6460/normal_ShopMenuBuyTotalPriceSet_50bb00
 * tail).  `st` (func_28E170 result) selects: 1 = confirm/buy, 2 = cancel,
 * other = adjust by +-10 driven by D_004845D0->f14 (1=inc,2=dec). */

typedef struct Panel {
    u8  pad00[0x14];
    s32 f14;
} Panel;

typedef struct QPanel {
    u8  pad00[8];
    s16 f08;
    u8  pad0A[6];
    s16 f10;
} QPanel;

typedef struct PO {
    s16 f00;
    u8  pad02[0x12];
    s8  f14;
} PO;

typedef struct PM {
    u8  pad00[0x10];
    PO *f10;
} PM;

typedef struct PS {
    PM *f00;
} PS;

typedef struct PR {
    u8  pad00[0x160];
    s64 f160;
} PR;

typedef struct PC {
    u8    pad00[0x18];
    void *f18;
} PC;

extern Panel *D_004845D0;      /* gp - 0xBA0 */
extern void  *D_004845C4;      /* gp - 0xBAC */
extern void  *D_004845CC;      /* gp - 0xBA4 */
extern PS    *D_00484644;      /* gp - 0xB2C */
extern u8     D_00484630;      /* gp - 0xB40 */
extern f32    D_0047D4BC;
extern u8 D_004B2570[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyQtyState_50d1b0(void *a, s32 b)
{
    s32 st;
    PM *m;
    PC *ctx;
    QPanel *pnl;
    s32 t;
    s32 qty;
    s32 w;
    PO *o;
    s32 x;
    s64 lim;
    s32 q;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_004845D0, 0x7533, 0);
    }

    pnl = ((QPanel *)UiEntryListGetCurrentData_28ec60(D_004845D0));
    w = pnl->f10;
    st = MenuGridCursorInput_28e170(D_004845D0, D_004B2570, 1, 0);
    ctx = ((PC *)GetGameData_1fede0());

    m = D_00484644->f00;
    if (m == NULL) {
        return 0;
    }
    o = m->f10;
    t = 0;
    if (o->f14 >= 0) {
        t = o->f14;
    }

    if (st == 1) {
        PlayMenuSe_289ef0(5);
        lim = ((PR *)ctx->f18)->f160;
        qty = pnl->f10;
        if (lim < (s16)qty * ShopRowGetPrice_3ce6e0(D_00484644)) {
            D_00484630 = 1;
            StateMachineSetState_28ede0(D_004845C4, 0x753E, 0);
        } else if (InvAddItemCheckedMaybe_3c6460(ctx->f18, m->f10->f00, qty, t, 0) == 0) {
            D_00484630 = 2;
            StateMachineSetState_28ede0(D_004845C4, 0x753E, 0);
        } else {
            UiFadeWidgetAlpha_290690(D_004845CC, 0x48, 0.0f, D_0047D4BC, -1.0f);
            UiFadeWidgetAlpha_290690(D_004845CC, 0x46, 0.0f, D_0047D4BC, -1.0f);
            StateMachineSetState_28ede0(D_004845C4, 0x753B, 0);
        }
    } else if (st == 2) {
        PlayMenuSe_289ef0(6);
        StateMachineSetState_28ede0(D_004845C4, 0x753A, 0);
    } else {
        x = D_004845D0->f14;
        if (!(x != 1 && x != 2)) {
            if (x == 1) {
                q = pnl->f10 + 10;
                pnl->f10 = q;
                if ((s16)q > 99) {
                    pnl->f10 = 99;
                } else if (pnl->f08 < (s16)q) {
                    pnl->f10 = pnl->f08;
                }
            } else if (x == 2) {
                q = pnl->f10 - 10;
                pnl->f10 = q;
                if ((s16)q <= 0) {
                    pnl->f10 = 1;
                }
            }
            UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), 1, 0);
            UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), 1, 1);
            UiSetSpriteFlags_290bd0(D_004845CC, 0x4F, (long long)(8), 1, 2, 0);
            lim = ((PR *)ctx->f18)->f160;
            if (lim < pnl->f10 * ShopRowGetPrice_3ce6e0(D_00484644)) {
                UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), -1, 1);
                UiSetSpriteFlags_290bd0(D_004845CC, 0x4F, (long long)(8), -1, 2, 0);
            }
            if (InvAddItemCheckedMaybe_3c6460(ctx->f18, m->f10->f00, pnl->f10, t, 0) == 0) {
                UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), -1, 0);
            }
            UiSetWidgetSubItemValue_291250(D_004845CC, 0x4F, 0, (long long)(pnl->f10));
            normal_ShopMenuBuyTotalPriceSet_50bb00(ShopRowGetPrice_3ce6e0(D_00484644), pnl->f10);
        }
    }

    if (w != pnl->f10) {
        PlayMenuSe_289ef0(4);
    }
    return 1;
}
