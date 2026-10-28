/* rgp:protos */
#define RGP_SELF_normal_TransMenuStep_5165c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005165C0 -- the gameplay scene's per-frame FADE driver.  gp-0xA24
 * is the phase, gp-0xA18 its timer, and normal_TransMenuIsQuickOpen_514a00 splits the frame
 * into a "still loading" arm (which snaps the widgets with func_2907A0) and a
 * "loaded" arm (which ramps them with func_290690 and waits for 0x7532 to
 * reach 1.0f before handing the camera to func_321xxx).  Globals and their
 * types are the ones normal_TransMenuInit_516aa0.c already proved byte-identical. */

typedef struct Act { u8 pad00[0x30]; s16 f30; } Act;
typedef struct Ent { u8 pad00[0x18]; Act *f18; } Ent;
typedef struct Obj { u8 pad00[0x14]; } Obj;

extern u8 normal_D_00527F10[];

extern s16   D_004806C8;          /* gp - 0x4AA8 */
extern Obj  *D_004846E8;          /* gp - 0xA88  */
extern Obj  *D_004846EC;          /* gp - 0xA84  */
extern Obj  *D_004846F0;          /* gp - 0xA80  */
extern Obj  *D_004846F4;          /* gp - 0xA7C  */
extern Obj  *D_004846F8;          /* gp - 0xA78  */
extern s16   D_00484700;          /* gp - 0xA70  */
extern s8    D_0048472C;          /* gp - 0xA44  */
extern s16   D_0048474C;          /* gp - 0xA24  */
extern s16   D_00484750;          /* gp - 0xA20  */
extern f32   D_00484758;          /* gp - 0xA18  */
extern f32   D_0047D958;          /* gp - 0x7818 */
extern f32   D_0047D95C;          /* gp - 0x7814 */
extern f32   D_0047D1FC;          /* gp - 0x7F74 */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_TransMenuStep_5165c0(void)
{
    f32   t;
    Ent  *e;
    void *ob;
    void *pl;
    void *fb;
    s32   n;
    s32   m;

    if (D_0048474C != 0) {
        t = D_00484758 + D_0047D958;
        D_00484758 = t;
        if (!(t <= 0.0f)) {
            D_00484758 = t - D_0047D1FC;
        }
        if (normal_TransMenuIsQuickOpen_514a00() != 0) {
            if (D_00484750 == 1) {
                if (D_004806C8 == 1) {
                    TaskSetRenderTasksEnabled_287b90(0);
                    SceneOverlayModeOn_288340();
                    UiSetWidgetsVisibleById_291110(D_004846EC, 0x84D1, 1, 1);
                    UiSetWidgetAlpha_2907a0(D_004846EC, 0x84D1, 1.0f);
                    UiSetWidgetsVisibleById_291110(D_004846E8, 0x7532, 1, 1);
                    UiSetWidgetAlpha_2907a0(D_004846E8, 0x7532, 1.0f);
                    UiSetWidgetsVisibleById_291110(D_004846E8, 0x7533, 1, 1);
                    UiSetWidgetAlpha_2907a0(D_004846E8, 0x7533, 1.0f);
                    UiSetWidgetsVisibleById_291110(D_004846E8, 0x75D1, 0, 1);
                    D_0048474C = 2;
                    D_004806C8 = 0;
                    ScreenFadeBlockFadeOutColor_1782a0(normal_D_00527F10, 1, 1.0f, 1.0f, 1.0f);
                    ScreenFadeBlockStep_177f90(normal_D_00527F10);
                    StateMachineSetState_28ede0(&D_00484700, 2, 1);
                }
            }
        } else {
            if (D_00484750 == 1) {
                if (D_004806C8 == 1) {
                    UiSetWidgetsVisibleById_291110(D_004846EC, 0x84D1, 1, 1);
                    UiFadeWidgetAlpha_290690(D_004846EC, 0x84D1, 1.0f, D_0047D95C, -1.0f);
                    UiSetWidgetsVisibleById_291110(D_004846EC, 0x7532, 1, 1);
                    UiFadeWidgetAlpha_290690(D_004846E8, 0x7532, 1.0f, D_0047D95C, -1.0f);
                    UiSetWidgetsVisibleById_291110(D_004846E8, 0x7533, 1, 1);
                    UiFadeWidgetAlpha_290690(D_004846E8, 0x7533, 1.0f, D_0047D95C, -1.0f);
                    UiSetWidgetPos_290f60(D_004846E8, 0x7556, 0x26, 0x6A);
                }
            }
            if (D_004806C8 == 1) {
                if (!(UiGetWidgetAlpha_290770(D_004846E8, 0x7532) < 1.0f)) {
                    D_0048474C = 2;
                    D_004806C8 = 0;
                    StateMachineSetState_28ede0(&D_00484700, 1, 1);
                    e = ((Ent *)GetGameData_1fede0());
                    ob = GetMapMgr_201a90();
                    if (ob != NULL) {
                        n = 0;
                        MapSlotsFindBlockById_1e49b0(ob, e->f18->f30, &n);
                        if (n != 0) {
                            if (MinimapFindForArea_1dcb50(n) != 0) {
                                pl = GetMinimapMgr_201a70();
                                if (pl != NULL) {
                                    MinimapMgrSetViewMode_321c00(pl, 1);
                                    MinimapMgrSetScreenAnchorPos_321b60(pl, 0x10, 0x20);
                                    MinimapMgrSetSize_321ac0(pl, 0x1E0, 0x1A0);
                                    MinimapMgrSetWinSize_321a20(pl, 0x1E0, 0x180);
                                    MinimapMgrFadeInStart_321e80(pl, 15.0f);
                                }
                                D_0048472C = 1;
                            }
                        }
                    }
                    UiSetWidgetsVisibleById_291110(D_004846E8, 0x75D1, 1, 1);
                    UiFadeWidgetAlpha_290690(D_004846E8, 0x75D1, 1.0f, D_0047D95C, 0.0f);
                    normal_TransMenuBobIconMoveTo_518420(0xF4, 0xBE, -1);
                    if (ob != NULL) {
                        MapMgrCaptionRelease_1e2d10(ob);
                    }
                }
            }
        }
        normal_TransMenuResPoll_5181d0();
        normal_TransMenuSubResPoll_517d40();
        ob = GetMapMgr_201a90();
        if (ob != NULL) {
            e = ((Ent *)GetGameData_1fede0());
            m = 0;
            MapSlotsFindBlockById_1e49b0(ob, e->f18->f30, &m);
            if (m != 0) {
                if (D_0048472C != 0) {
                    MinimapFindForArea_1dcb50(m);
                    pl = GetMinimapMgr_201a70();
                    if (pl != NULL) {
                        MinimapMgrUpdate_322030(pl, 0);
                    }
                }
            }
        }
        normal_TransMenuBobIconStep_518450(0, 0, 0);
        fb = GetDrawCtxNameTable_15de40();
        if (fb != NULL) {
            TexGroupUpdateAnim_157ca0(fb, 0x32C, 1.0f);
        }
        UiUpdateWidgets_2913a0(D_004846E8);
        UiUpdateWidgets_2913a0(D_004846EC);
        UiUpdateWidgets_2913a0(D_004846F0);
        UiUpdateWidgets_2913a0(D_004846F4);
        UiUpdateWidgets_2913a0(D_004846F8);
        StateMachineUpdate_28ed70(&D_00484700);
        ScreenFadeBlockStep_177f90(normal_D_00527F10);
    }
}
