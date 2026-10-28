/* rgp:protos */
#define RGP_SELF_normal_TransWarpListState_51c2e0 1
#include "port/game_protos.h"
#line 1
/* === SESSION 49 (2026-09-08): MATCH.  269 words, 201 bad -> 0.  MERGED into
 * config/ocunits/normal.txt.  Every edit came from ONE new screen,
 * build/wf-normal/s49/relscan.py -- the RELOCATION STREAM, ours vs retail.
 * Every other screen on this board MASKS relocated words out on both sides
 * (it has to; our object carries 0 where retail carries an address), and
 * mdiff decodes the OPCODE only -- so a wrong/missing/extra GLOBAL or CALL
 * cost ZERO on all of them.  relscan named four facts here in one run:
 *
 * 1. `cnt = 0;` sat AFTER the counting loop and `total = D_00484850;` sat
 *    four statements too late, so BOTH the loop and the load were DEAD and
 *    the object referenced 0x00484850 zero times where retail does twice.
 *    Retail's two references are ONE statement: the `beql` duplicates the
 *    `lw -0x920($28)` into its delay slot.  WARN the s31 six-deck sweep
 *    (31,338 arms) INSTALLED both misplacements -- `MV_cnt_L127_T135_SAFE_mov`
 *    and `MV_D_00484854_L151_T125_DEREF_mov` -- because each scored better
 *    alone.  A statement-move deck that only reads a bad-count will happily
 *    kill a loop.
 * 2. `top` and `sel` are s32, not s16: retail passes them to
 *    normal_TransWarpListRowsFill_51b4b0 / normal_TransWarpRowHighlight_51acb0 with no dsll32/dsra32 pair,
 *    and BOTH callees are MERGED with the signature `s32 f(s32)`
 *    ([[merged-callee-signature-oracle]]) while this file declared
 *    `void f(s16)`.  Four words.
 * 3. `D_00484854 = h->f12;` is the LAST statement of the case-2 block, AFTER
 *    `h->f12 = sel;` -- retail READS IT BACK (`lh $2,0x12($17)` then
 *    `sh $2,-0x91C($28)`), it does not reuse the register
 *    ([[mwcc-readback-carries-conversion]]).
 * 4. `p = D_00484870;` must be written BELOW `normal_TransWarpListExpand_51aef0(...)`, not
 *    above it.  Retail reloads the gp global after the call because it lives
 *    in a caller-saved register; written above, mwcc parks it in a
 *    callee-saved one and the reload disappears.  That ONE WORD was the last
 *    length difference.  WARN `p = (Ent *)(s32)D_00484870;` -- the identity-cast
 *    pin -- is INERT here; only the statement's POSITION reaches it.
 * 5. `func_1E49B0` RETURNS a value (`daddu $19,$2,$0`) and it is the argument
 *    to `func_1DFEF0`, not `sub`.  This file declared it `void`.  Captured in
 *    the dead local `r` (free: [[normal-session45-levers]] -- a named temp's
 *    whole cost is its declaration slot).  201 -> 13 bad on this one edit.
 * 6. The last 13 were a clean 3-cycle over {r, pp, v} in $17/$18/$19.  All
 *    six declaration permutations were swept; `r, pp, v` is the MATCH and it
 *    is DESCENDING register order ([[mwcc-gpr-decl-order-map]]): the trio is
 *    handed $19,$18,$17 in declaration order.  The other five score 7-13.
 * Everything below predates this and its numbers are history. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_D_00484854_L151_T125_DEREF_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 272 words, ? bad   after: 271 words, ? bad   (retail 269 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_cnt_L127_T135_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 274 words, ? bad   after: 272 words, ? bad   (retail 269 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x0051C2E0 -- the 0x4B2570 text-box driver's per-frame poll.
 * func_28E170 returns a MODE (1 = a row was chosen, 2 = the box closed).
 * Mode 1 dispatches on the selected D_00484870 row's f00 kind:
 *   1 = a leaf, 2 = a list whose window is re-clamped to five visible rows,
 *   3 = a scene jump.
 * Mode 2 hands the current selection to the party/inventory chain.
 * Session 31 lane a7, FRESH unit. */

typedef struct Hdl {
    u8  pad00[0x12];
    s16 f12;
    u8  pad14[0x16 - 0x14];
    s16 f16;
} Hdl;

typedef struct Ent {
    s16   f00;
    u8    pad02[0x8 - 0x2];
    void *f08;
    void *f0C;
    u8    pad10[0x30 - 0x10];
} Ent;

typedef struct Sub {
    u8  pad00[0x30];
    s16 f30;
} Sub;

typedef struct Obj {
    u8   pad00[0x18];
    Sub *f18;
} Obj;

typedef struct Pl {
    u8    pad000[0x510];
    void *f510;
    void *f514;
} Pl;

extern u8 D_004B2570;

extern s32   D_00484720;   /* gp - 0xA50 */
extern Ent  *D_00484870;   /* gp - 0x900 */
extern s32   D_00484850;   /* gp - 0x920 */
extern s16   D_00484854;   /* gp - 0x91C */
extern void *D_00484874;   /* gp - 0x8FC */
extern void *D_00484710;   /* gp - 0xA60 */
extern void *D_0048470C;   /* gp - 0xA64 */
extern f32   D_0048484C;   /* gp - 0x924 */
extern s32   D_00484884;   /* gp - 0x8EC */
extern u8    D_0048476C;   /* gp - 0xA04 */
extern s32   D_00484860;   /* gp - 0x910 */

extern f32   D_0047D9E8;   /* gp - 0x7788 */
extern f32   D_0047D9EC;   /* gp - 0x7784 */
extern f32   D_0047D9DC;   /* gp - 0x7794 */

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
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransWarpListState_51c2e0(void)
{
    s32   buf[7] __attribute__((aligned(16)));
    s32   n;
    s32   mode;
    Hdl  *h;
    s32   idx;
    Ent  *p;
    s32   cnt;
    s32   total;
    s32   top;
    s32   sel;
    Obj  *obj;
    Sub  *sub;
    void *pl;
    Sub  *r;
    Pl   *pp;
    void *v;

    mode = MenuGridCursorInput_28e170(D_00484720, &D_004B2570, 0, 0);
    h = ((Hdl *)UiEntryListGetCurrentData_28ec60(D_00484720));
    normal_TransWarpMinimapFocus_51a7a0(h);
    if (mode == 1) {
        idx = h->f12 + h->f16;
        if (D_00484870[idx].f00 == 1) {
            normal_TransWarpListExpand_51aef0(D_00484870[idx].f0C);
            p = D_00484870;
            while (p != 0) {
                if (p->f00 == 2) {
                    break;
                }
                p++;
            }
            normal_TransWarpListRowsFill_51b4b0(h->f16);
            normal_TransWarpScrollBarUpdate_51ac30();
            UiSetWidgetPos_290f60(D_00484710, 0x75D9, 0x1E5,
                        (s32)(295 + h->f16 * D_0048484C));
        } else if (D_00484870[idx].f00 == 2) {
            normal_TransWarpListCollapse_51ad60(D_00484870[idx].f0C);
            p = D_00484870;
            cnt = 0;
            while (p != 0) {
                if (p->f0C == D_00484870[idx].f0C) {
                    break;
                }
                cnt++;
                p++;
            }
            total = D_00484850;
            if (total - cnt < 5 && total - h->f16 < 5 && total >= 5) {
                top = total - 5;
                sel = 5 - (total - cnt);
            } else {
                top = h->f16;
                sel = h->f12;
            }
            if (total < 6) {
                sel += top;
                top = 0;
            }
            normal_TransWarpListRowsFill_51b4b0(top);
            normal_TransWarpRowHighlight_51acb0(sel);
            h->f12 = sel;
            h->f16 = top;
            D_00484854 = h->f12;
            normal_TransWarpScrollBarUpdate_51ac30();
            UiSetWidgetPos_290f60(D_00484710, 0x75D9, 0x1E5,
                        (s32)(295 + h->f16 * D_0048484C));
        } else if (D_00484870[idx].f00 == 3) {
            if (D_00484874 != D_00484870[idx].f08) {
                GetGameData_1fede0();
                LeaderPlaceAtSavePoint_2f1fb0();
                normal_TransMenuSetWarpRequest_518640(1, D_00484870[idx].f08);
                StateMachineSetState_28ede0(D_0048470C, 4, 0);
                UiFadeWidgetAlpha_290690(D_00484710, 0x75DC, 0.0f, D_0047D9E8, -1.0f);
                UiFadeWidgetAlpha_290690(D_00484710, 0x75DB, 0.0f, D_0047D9E8, -1.0f);
                UiFadeWidgetAlpha_290690(D_00484710, 0x75D0, 0.0f, D_0047D9EC, -1.0f);
                UiFadeWidgetAlpha_290690(D_00484710, 0x75D2, 0.0f, D_0047D9DC, -1.0f);
                UiFadeWidgetAlpha_290690(D_00484710, 0x75D3, 0.0f, D_0047D9DC, -1.0f);
            }
        }
    } else if (mode == 2) {
        D_00484884 = 0;
        obj = (Obj *)GetGameData_1fede0();
        D_0048476C = PartyLocationGroupIdIsOneMaybe_3cb120(obj->f18);
        pl = GetMapMgr_201a90();
        if (pl != 0) {
            n = 0;
            sub = obj->f18;
            r = ((Sub *)MapSlotsFindBlockById_1e49b0(pl, sub->f30, &n));
            if (n != 0) {
                pp = ((Pl *)GetMinimapMgr_201a70());
                if (pp != 0) {
                    MinimapMgrTrackActiveSlot_321ea0(pp, MapDataGetName_1e7bf0(n));
                    v = pp->f514;
                    if (v == 0) {
                        v = pp->f510;
                    }
                    if (v != 0) {
                        MinimapSelectEntryByName_324a70(v, MapBlockGetOwnName_1dfef0(r), &D_00484860);
                        MinimapSetCenterPos_324870(v, &D_00484860);
                        r = MapSlotsFindBlockByName_1e4910(pl, MinimapGetEntryBlockName_324a40(v), 0);
                        if (r != 0) {
                            MapDataGetPosVec4_1e7740(r, buf);
                            MinimapSetTargetPosMaybe_324bb0(v, buf);
                        }
                    }
                }
            }
        }
        StateMachineSetState_28ede0(D_0048470C, 0xE, 0);
    }
    return 1;
}
