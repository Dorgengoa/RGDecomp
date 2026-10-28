/* rgp:protos */
#define RGP_SELF_normal_TransWarpListScrollState_51bdb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* SESSION 30: CLOSED, and by a single statement move.
 * Parked ONE WORD SHORT since s19 (0x228 vs 0x22c).  The pool-wide
 * DEFINING-STATEMENT MOVE deck (build/wf-normal/s30/mkmove30.py, 3,428 arms
 * over 54 units, every unit's identity arm reproducing its recorded bad
 * count) found it: `vis = 1;` moved from AFTER the `if (dx < -0x18)` guard to
 * BEFORE it.  s29's declaration deck could not reach this -- moving a
 * DECLARATION does not move a local's FIRST DEFINITION, and the callee-saved
 * map follows CREATION order ([[mwcc-callee-saved-creation-order]]).
 * The s29 live-knob screen had also made this unit right-length on
 * `fastmath off`, at l1 6 -> 15, and it was correctly NOT installed: that
 * knob buys the length by moving the object further away.  The move buys it
 * at l1 6 -> 1, and the object is retail.
 * MERGED into config/ocunits/normal.txt session 30. */
/* !! PARKED, lane `ne` (research), session 19.  ONE WORD SHORT (0x228 vs 0x22c).
 * Every other word is byte-identical -- the diff is a single one-instruction
 * shift starting at 0x0051BEB4.  NOT in config/ocunits/normal.txt.
 *
 * ROUND TRIPS: 4.  MOVEMENT: 32 bad -> 1 word short, i.e. TWO levers closed
 * 32 bad words, and both CORRECT normal_TransWarpListCursorBobCb_51bbe0's park notes:
 *  * func_3242B0's 4th parameter is `s32`, NOT `u8`.  The local flagByte is
 *    the u8; retail's `andi $a3,$a0,0xFF` in BOTH branch-likely arms is the
 *    u8 -> s32 PROMOTION AT THE CALL.  Declaring the parameter `u8` deletes
 *    the andi entirely and shifts flagByte out of $a0.  Worth ~20 words here.
 *    0051bbe0's comment says a `u8` parameter "reproduces retail's per-arm
 *    andi" -- measured here, it does the opposite.
 *  * the last guard must NOT be `if (id < 0) goto fallback; cid = id;`.
 *    Writing `if (id < 0) { fallback: ...; } cid = id;` -- the join statement
 *    UNCONDITIONAL after the fallback block -- is what makes mwcc emit
 *    retail's `bgezl $s2,+5` with `daddu $a2,$s2,$0` duplicated into the
 *    delay slot ([[mwcc-branch-likely-duplication]]).  Worth 2 words.
 *
 * RESIDUE: retail computes `h8 = h + 8` (`addiu $v1,$s0,0x8`) as the SECOND
 * instruction of the float block, at 0x0051BEB4, and leaves guard 1's delay
 * slot for `vis = 1`; mwcc sinks h8 into that delay slot instead and leaves
 * one fewer nop.  MEASURED INERT on that scheduling slot (3 arms, same
 * object): h8 before dx, h8 between dx and dy, h8 declared FIRST in the local
 * list.  This is a scheduler slot, not a source-order lever. */

/* normal 0x0051BDB0 -- the SIBLING of normal_TransWarpListCursorBobCb_51bbe0 (parked, right
 * length / 34 bad).  Same func_15DE80 / func_1451E0 / func_1451D0 /
 * func_1E49B0 / func_1DCB50 / func_201A70 / func_324270 chain, but
 *   - no normal_TransWarpCursorBob_51c720 call,
 *   - `q` is initialised straight from func_1DCB50's RETURN (retail puts
 *     `daddu $20,$2,$0` in `jal func_201A70`'s own delay slot), which is the
 *     arm 0051bbe0's park item 1 could not reach with `q = pl;`, and
 *   - a trailing func_2910A0 / 0x1B poll block.
 *
 * Arms carried over from 0051bbe0's proven set:
 *   - nested `if (cond != 0) { ... }` all the way down to ONE `return 1;`
 *   - `flagByte` is a genuine u8 parameter of func_3242B0 (the per-arm
 *     `andi $a3,$a0,0xFF` tail-merge), declared and assigned BEFORE `id = -1`
 *   - `h8 = h + 8;` hoisted immediately after func_3242B0
 *   - `vis = 1;` placed AFTER the first guard (retail has `daddiu $16,$0,1`
 *     in that guard branch's delay slot) */

typedef struct Pl {
    u8    pad000[0x510];
    void *f510;
    void *f514;
} Pl;

typedef struct Hdl {
    u8  pad000[0x16];
    s16 f016;
} Hdl;

extern s32   D_00484760;   /* gp - 0xA10 */
extern s32   D_00484764;   /* gp - 0xA0C */
extern s32   D_00484768;   /* gp - 0xA08 */
extern s32   D_00484878;   /* gp - 0x8F8 */
extern void *D_00484710;   /* gp - 0xA60 */
extern void *D_0048470C;   /* gp - 0xA64 */
extern s32   D_00484720;   /* gp - 0xA50 */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransWarpListScrollState_51bdb0(void)
{
    s32   h8;
    void *fb;
    s32   w;
    s32   h;
    void *p;
    s32   n;
    void *ev;
    s32   code;
    Pl   *pl;
    void *q;
    s32   res1;
    s32   res2;
    s32   id;
    u8    flagByte;
    f32   pos[2];
    s32   dx;
    s32   dy;
    s32   cid;
    u8    vis;

    fb = GetDrawCtx_15de80();
    w = DrawEnvGetWidth_1451e0(fb);
    h = DrawEnvGetHeight_1451d0(fb);
    GetGameData_1fede0();
    p = GetMapMgr_201a90();
    if (p != 0) {
        n = 0;
        MapSlotsFindBlockById_1e49b0(p, D_00484878, &n);
        if (n != 0) {
            q = MinimapFindForArea_1dcb50(n);
            pl = ((Pl *)GetMinimapMgr_201a70());
            if (pl != 0) {
                q = pl->f514;
                if (q == 0) {
                    q = pl->f510;
                }
            }
            if (q != 0) {
                MinimapScrollStep_3243f0(q);
                res1 = MinimapGetEntryIndex_324270(q, 1);
                res2 = MinimapGetEntryIndex_324270(q, 0);
                flagByte = 1;
                id = -1;
                if (D_00484768 == res1) {
                    id = res1;
                } else if (D_00484768 == res2) {
                    id = res2;
                    flagByte = 0;
                }
                MinimapGetScaledXZMaybe_3242b0(q, &pos[0], &pos[1], flagByte);
                vis = 1;
                dx = (s32)((f32)D_00484760 - pos[0]);
                h8 = h + 8;
                dy = (s32)((f32)D_00484764 - pos[1]);
                if (dx < -0x18) {
                    goto fallback;
                }
                if (dx >= w) {
                    goto fallback;
                }
                if (dy < -0x2A) {
                    goto fallback;
                }
                if (dy >= h8) {
                    goto fallback;
                }
                if (id < 0) {
                fallback:
                    dx = -0x64;
                    vis = 0;
                    dy = dx;
                }
                cid = id;
                normal_TransMenuBobIconMoveTo_518420(dx, dy, cid);
                normal_TransMenuBobIconShow_5183c0(vis);
            }
        }
    }
    UiGetWidgetPos_2910a0(D_00484710, 0x75DA, &ev, &code);
    if (code == 0x1B || code == -0x1B) {
        normal_TransWarpListRowsFill_51b4b0(((Hdl *)UiEntryListGetCurrentData_28ec60(D_00484720))->f016);
        UiSetWidgetPos_290f60(D_00484710, 0x75DA, 0, 0);
        UiSetWidgetPos_290f60(D_00484710, 0x75D4, 0, 0);
        StateMachineSetState_28ede0(D_0048470C, 0xD, 0);
    }
    return 1;
}
