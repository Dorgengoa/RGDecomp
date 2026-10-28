/* rgp:protos */
#define RGP_SELF_normal_TransMenuDraw_5163a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub {
    u8  pad000[0x30];
    s16 f030;
    u8  pad032[0x15C];
    s16 f18E;
} Sub;

typedef struct Ev {
    u8   pad00[0x18];
    Sub *f18;
} Ev;

typedef struct Pl {
    u8    pad000[0x510];
    void *f510;
    void *f514;
} Pl;

extern u8    normal_D_00526710[0x10];
extern u8    normal_D_00527F10[0x10];

extern f32   D_00480700;   /* gp - 0x4A70 */
extern f32   D_00480704;   /* gp - 0x4A6C */
extern f32   D_00480708;   /* gp - 0x4A68 */
extern f32   D_0048070C;   /* gp - 0x4A64 */
extern void *D_004846E8;   /* gp - 0xA88  */
extern void *D_004846EC;   /* gp - 0xA84  */
extern void *D_004846F0;   /* gp - 0xA80  */
extern void *D_004846F4;   /* gp - 0xA7C  */
extern void *D_004846F8;   /* gp - 0xA78  */
extern s8    D_0048472C;   /* gp - 0xA44  */
extern s16   D_0048474C;   /* gp - 0xA24  */
extern f32   D_00484758;   /* gp - 0xA18  */

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

void normal_TransMenuDraw_5163a0(void)
{
    s32   n;
    f32   pos[2];
    f32   v[4] __attribute__((aligned(16)));
    void *p;
    Ev   *e;
    void *r;
    void *t;
    void *q;
    s16  *s;
    s32   w;
    s32   h;
    Pl   *pl;

    if (D_0048474C != 0) {
        UiDrawWidgets_291910(D_004846EC);
        p = GetMapMgr_201a90();
        if (p != 0) {
            e = ((Ev *)GetGameData_1fede0());
            n = 0;
            MapSlotsFindBlockById_1e49b0(p, e->f18->f030, &n);
            if (n != 0) {
                r = MinimapFindForArea_1dcb50(n);
                pl = ((Pl *)GetMinimapMgr_201a70());
                if (pl != 0) {
                    r = pl->f510;
                    if (pl->f514 != 0) {
                        r = pl->f514;
                    }
                }
                if (r != 0) {
                    v[0] = D_00480700;
                    v[1] = D_00480704;
                    v[2] = D_00480708;
                    v[3] = D_0048070C;
                    t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), e->f18->f18E);
                    if (t != 0) {
                        CharaGetPos_2388a0(t, v);
                    }
                    if (D_0048472C != 0) {
                        MapMgrMinimapDraw_1e2820(p, v, 0.0f);
                        q = GetDrawCtx_15de80();
                        s = ((s16 *)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), normal_D_00526710, 0x32D));
                        if (s != 0) {
                            DrawListAddTexLoad_1418c0(q, *s, 1.0f);
                        }
                        MinimapGetScaledXZMaybe_3242b0(r, &pos[0], &pos[1], 1);
                        w = DrawEnvGetWidth_1451e0(q);
                        h = DrawEnvGetHeight_1451d0(q);
                        normal_TransMenuMinimapMarkersDrawMaybe_5174d0(q, (s32)((f32)(w / 2) - pos[0]),
                                            (s32)((f32)(h / 2) - pos[1]), s, D_00484758);
                    }
                }
            }
        }
        UiDrawWidgets_291910(D_004846E8);
        UiDrawWidgets_291910(D_004846F0);
        UiDrawWidgets_291910(D_004846F4);
        UiDrawWidgets_291910(D_004846F8);
        ScreenFadeBlockDraw_177540(normal_D_00527F10);
    }
}
