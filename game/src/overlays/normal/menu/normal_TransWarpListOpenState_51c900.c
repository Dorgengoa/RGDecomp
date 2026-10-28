/* rgp:protos */
#define RGP_SELF_normal_TransWarpListOpenState_51c900 1
#include "port/game_protos.h"
#line 1
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_j_L176_T177_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 309 words, 36 bad   after: 309 words, 16 bad   (retail 309 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_D_00484854_L190_T184_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 310 words, ? bad   after: 309 words, 36 bad   (retail 309 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
#include "vec.h"
/* normal 0x0051C900 -- FRESH, session 31 lane a5.
 * Sibling of normal_TransWarpOpenState_51cde0 / normal_TransWarpListScrollState_51bdb0 (both merged):
 * the f(void *, s32) state-handler family, guard on arg 2, two early
 * `return 0`s off func_3C97E0, tail func_28EDE0(D_0048470C, 0xD, 0).
 * `break 0,7` => #pragma divbyzerocheck on. */
#pragma divbyzerocheck on

typedef struct W   { u8 pad00[0x30]; s16 f30; } W;
typedef struct Ctx { u8 pad00[0x18]; W *f18; } Ctx;
typedef struct Obj { s16 f00; u8 pad02[0x20 - 2]; f32 f20; f32 f24; f32 f28;
                     u8 pad2C[0x40 - 0x2C]; s32 f40; } Obj;
typedef struct Pl  { u8 pad00[0x510]; void *f510; } Pl;
typedef struct Hd  { u8 pad00[0x12]; s16 f12; u8 pad14[2]; s16 f16; } Hd;
typedef struct Ent { u8 pad00[8]; s16 f08; s16 f0A; } Ent;
typedef struct Hold { u8 pad00[0x20]; Ent *f20; } Hold;
typedef struct E   { u8 pad00[8]; s32 f08; u8 pad0C[4]; s32 f10;
                     u8 pad14[0x30 - 0x14]; } E;

extern f32   D_0047D248;          /* gp - 0x7F28 */
extern f32   D_0047D288;          /* gp - 0x7EE8 */
extern f32   D_0047D920;          /* gp - 0x7850 */
extern f32   D_0047D9F0;          /* gp - 0x7780 */
extern f32   D_0047D9F4;          /* gp - 0x777C */
extern f32   D_00480720;          /* gp - 0x4A50 */
extern f32   D_00480724;          /* gp - 0x4A4C */
extern f32   D_00480728;          /* gp - 0x4A48 */
extern f32   D_0048072C;          /* gp - 0x4A44 */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_00484720;          /* gp - 0xA50  */
extern s32   D_00484760;          /* gp - 0xA10  */
extern s32   D_00484764;          /* gp - 0xA0C  */
extern s32   D_00484848;          /* gp - 0x928  */
extern f32   D_0048484C;          /* gp - 0x924  */
extern s16   D_00484854;          /* gp - 0x91C  */
extern u64   D_00484860;          /* gp - 0x910; declared <= 8 B so mwcc
                                     small-datas it and the 16-byte store
                                     stays gp-relative (sq $2,-0x910($28)) */
extern E    *D_00484870;          /* gp - 0x900  */
extern s32   D_00484874;          /* gp - 0x8FC  */

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

s32 normal_TransWarpListOpenState_51c900(void *a, s32 b)
{
    Ctx  *ctx;
    void *fb;
    s32   w;
    s32   h;
    Obj  *o;
    void *p;
    s32   n;
    void *q;
    Pl   *pl;
    Obj  *o2;
    s32   r;
    E    *e;
    s32   i;
    s32   j;
    Hold *hd;
    Ent  *en;
    s32   v;
    Hd   *hh;
    Vec4  pos __attribute__((aligned(16)));

    if (b != 0) {
        ctx = ((Ctx *)GetGameData_1fede0());
        fb = GetDrawCtx_15de80();
        w = DrawEnvGetWidth_1451e0(fb);
        h = DrawEnvGetHeight_1451d0(fb);
        UiSetWidgetPos_290f60(D_00484710, 0x7534, -0x78, -0x64);
        UiSetWidgetAlpha_2907a0(D_00484710, 0x7534, 1.0f);
        UiSetWidgetPos_290f60(D_00484710, 0x753C, 0x50, 0x9C);
        UiSetWidgetPos_290f60(D_00484710, 0x7537, 0x53, 0x9F);
        UiMoveWidgetUniform_290f50(D_00484710, 0x753C, 0x7A, 0x9C, 0.25f, 0);
        UiMoveWidgetUniform_290f50(D_00484710, 0x7537, 0x7D, 0x9F, 0.25f, 0);
        UiFadeWidgetAlpha_290690(D_00484710, 0x75DC, 1.0f, D_0047D9F0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x75DB, D_0047D920, D_0047D9F0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x75D0, 1.0f, D_0047D9F0, -1.0f);
        UiSetWidgetPos_290f60(D_00484710, 0x75D6, 0x91, 0x106);
        UiSetWidgetPos_290f60(D_00484710, 0x75D7, 0xE, 0x12F);
        UiGetWidgetPos_2910a0(D_00484710, 0x75D1, &D_00484760, &D_00484764);
        UiSetWidgetPos_290f60(D_00484710, 0x75DE, w / 2, h / 2);
        UiSetWidgetPos_290f60(D_00484710, 0x75D2, 0x94, 0x128);
        UiFadeWidgetAlpha_290690(D_00484710, 0x75D2, D_0047D288, D_0047D9F4, -1.0f);
        UiSetWidgetPos_290f60(D_00484710, 0x75D3, 0x94, 0x128);
        UiFadeWidgetAlpha_290690(D_00484710, 0x75D3, D_0047D248, D_0047D9F4, -1.0f);
        D_00484874 = -1;
        o = ((Obj *)SavePointGetLastRecMaybe_3c97e0(ctx->f18));
        if (o == 0) {
            return 0;
        }
        if ((o->f40 & 1) == 0) {
            return 0;
        }
        normal_TransWarpListBuild_51b120(TranspRowGetGroupIdMaybe_426560(o));
        p = GetMapMgr_201a90();
        if (p != 0) {
            n = 0;
            MapSlotsFindBlockById_1e49b0(p, ctx->f18->f30, &n);
            if (n != 0) {
                q = MinimapFindForArea_1dcb50(n);
                pl = ((Pl *)GetMinimapMgr_201a70());
                if (pl != 0) {
                    q = pl->f510;
                }
                if (q != 0) {
                    pos.x = D_00480720;
                    pos.y = D_00480724;
                    pos.z = D_00480728;
                    pos.w = D_0048072C;
                    o2 = ((Obj *)SavePointGetLastRecMaybe_3c97e0(ctx->f18));
                    if ((o2 != 0) && (o2->f40 & 1)) {
                        D_00484874 = o2->f00;
                        pos.x = o2->f20;
                        pos.y = o2->f24;
                        pos.z = o2->f28;
                    }
                    if (pl != 0) {
                        MinimapMgrSetCenterPos_321910(pl, &pos.x);
                    }
                    r = MinimapGetCurOrPendingEntry_32a920(q);
                    if (r != 0) {
                        D_00484848 = r + 0x54;
                    }
                    *(u128 *)&D_00484860 = *(u128 *)&pos;
                }
            }
        }
        e = D_00484870;
        i = 0;
        while (e != 0) {
            if (D_00484874 == e->f08) {
                break;
            }
            i++;
            e++;
        }
        hd = ((Hold *)UiFindWidget_290460(D_00484710, 0x75D8));
        if (hd == 0) {
            return 0;
        }
        en = hd->f20;
        if (en == 0) {
            return 0;
        }
        v = D_00484870[i].f10;
        en->f08 = (s16)((v % 3) * 0x54);
        en->f0A = (s16)((D_00484870[i].f10 / 3) * 0x4A);
        j = 0;
        if (i > 4) {
            j = i - 4;
        }
        i = (i > 4) ? 4 : i;
        normal_TransWarpListRowsFill_51b4b0(j);
        normal_TransWarpRowHighlight_51acb0(i);
        UiEntryListSelectByTag_28ea90(D_00484720, 8, 0);
        hh = ((Hd *)UiEntryListGetCurrentData_28ec60(D_00484720));
        hh->f12 = (s16)i;
        hh->f16 = (s16)j;
        D_00484854 = (s16)i;
        normal_TransWarpPreviewUpdate_51aa80(i + j);
        normal_TransWarpScrollBarUpdate_51ac30();
        UiSetWidgetPos_290f60(D_00484710, 0x75D9, 0x1E5,
                    (s32)((f32)0x127 + (f32)j * D_0048484C));
        normal_TransMenuSetWarpRequest_518640(0, -1);
    }
    StateMachineSetState_28ede0(D_0048470C, 0xD, 0);
    return 1;
}
