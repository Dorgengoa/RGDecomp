/* rgp:protos */
#define RGP_SELF_normal_TransWarpListCursorMoveCb_51b980 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051B980 -- the shop slot's model refresh, the sibling of
 * normal_FUN_0051A7A0 over the same 0x30-byte D_00484870 slot array.  The
 * slot BYTE OFFSET is CSE'd into $22 while the gp pointer is reloaded at every
 * use, which is what two plain `D_00484870[i]` subscripts around a call give.
 * `sh $3,-0x91C` at the tail writes the same `a->f12` the guard compared, so
 * the load is shared between the two arms of the branch.
 * The `adda.s`/`madd.s` pair is retail's OWN contraction -- naming the product
 * would break it, so the sum stays a single inline expression. */

typedef struct Ent {
    s16   f00;
    u8    pad02[0x14 - 0x02];
    void *f14;
    s8    f18;
    u8    pad19[0x30 - 0x19];
} Ent;                                      /* 0x30 */

typedef struct Wk { u8 pad00[0x12]; s16 f12; u8 pad14[2]; s16 f16; } Wk;
typedef struct Pl { u8 pad000[0x510]; void *f510; void *f514; } Pl;
typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;

extern f32   D_0047D34C;          /* gp - 0x7E24 */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern s8    D_0048476C;          /* gp - 0xA04  */
extern f32   D_0048484C;          /* gp - 0x924  */
extern s16   D_00484854;          /* gp - 0x91C  */
extern Ent  *D_00484870;          /* gp - 0x900  */
extern void *D_00484878;          /* gp - 0x8F8  */

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

s32 normal_TransWarpListCursorMoveCb_51b980(Wk *a)
{
    Vec   v __attribute__((aligned(16)));
    s32   n;
    void *r;
    s32   i;
    void *p2;
    Pl   *pl;
    void *h;
    s32   d;
    s32   k;

    normal_TransWarpRowHighlight_51acb0(a->f12);
    i = a->f12 + a->f16;
    D_00484878 = D_00484870[i].f14;
    GetGameData_1fede0();
    if (D_00484870[i].f00 == 3) {
        p2 = GetMapMgr_201a90();
        if (p2 != 0) {
            n = 0;
            MapSlotsFindBlockById_1e49b0(p2, D_00484878, &n);
            if (n != 0) {
                pl = ((Pl *)GetMinimapMgr_201a70());
                if (pl != 0) {
                    MinimapMgrTrackActiveSlot_321ea0(pl, MapDataGetName_1e7bf0(n));
                    h = pl->f514;
                    if (h == 0) {
                        h = pl->f510;
                    }
                    if (h != 0) {
                        r = MapSlotsFindBlockByName_1e4910(p2, MinimapGetEntryBlockName_324a40(h), 0);
                        if (r != 0) {
                            MapDataGetPosVec4_1e7740(r, &v);
                            MinimapSetTargetPosMaybe_324bb0(h, &v);
                        }
                    }
                }
            }
        }
        D_0048476C = D_00484870[i].f18 != 0;
    }
    normal_TransWarpPreviewUpdate_51aa80(i);
    if (D_00484854 == a->f12) {
        k = a->f12 + a->f16;
        if (a->f12 == 0) {
            normal_TransWarpListEdgeRowSet_51b310(0, k);
            d = 0x1B;
        } else if (a->f12 == 4) {
            normal_TransWarpListEdgeRowSet_51b310(1, k);
            d = -0x1B;
        }
        UiMoveWidget_290e00(D_00484710, 0x75DA, 0, d, 1, 0.0f, 4.0f);
        UiMoveWidget_290e00(D_00484710, 0x75D4, 0, d, 1, 0.0f, 4.0f);
        UiMoveWidgetUniform_290f50(D_00484710, 0x75D9, 0x1E5, (s32)(0x127 + a->f16 * D_0048484C), D_0047D34C, 0
);
        StateMachineSetState_28ede0(D_0048470C, 0xF, 0);
    }
    D_00484854 = a->f12;
    return 1;
}
