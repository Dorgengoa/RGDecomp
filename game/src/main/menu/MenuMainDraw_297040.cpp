/* rgp:protos */
#line 1
#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  Slot byte offset = 8 + 4*index,
   because mwcc's vtable carries two leading words. */

struct CObj {
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void v7() { VCM0(void, 0x24); }
};

struct Ent { u8 pad00[0x46]; s16 f46; };

extern "C" s16 D_004823A8;
extern "C" Ent *D_00482374;
extern "C" void *D_004823D0;
extern "C" u8  D_004823CC;
extern "C" s32 D_004823D4;
extern "C" void *D_00482388;
extern "C" u8 D_004DB190[];
extern "C" u8 D_004DB1B0[];
extern "C" u8 D_004DB1D0[];
extern "C" u8 D_004DB220[];
extern "C" u8 D_004DB240[];

extern "C" void UiDrawWidgets_291910(u8 *);
extern "C" void InsectCageSceneDraw_389ed0(void);
extern "C" void DebugItemListDrawIfShown_299d60(u8 *);
extern "C" void DebugItemIconGridDrawInfo_29a680(u8 *);
extern "C" float MenuFadeDraw_29fe50(Ent *);
extern "C" void MenuItemModelDraw_2a7090(int, int, int, int);
extern "C" void *GetDrawCtx_15de80(void);
extern "C" void DrawListAddTexLoad_1418c0(void *, s32, f32);
extern "C" void CameraSetViewFromCameraBase_142dd0(void *, s32, int, int);
extern "C" void DrawListAddCameraMatrixPacket_1481b0(void *);
extern "C" void DrawListAddViewPacket_1482e0(void *);
extern "C" void MenuWeaponCombineResultModelDraw_2a84f0(void);
extern "C" void MenuMobPreviewDraw_35fa50(void *);

extern "C" void MenuMainDraw_297040(void)
{
    s32 v;
    void *dl;

    v = D_004823A8;
    if (v == 0) {
        return;
    }
    if ((s16)v < 2) {
        UiDrawWidgets_291910(D_004DB190);
        return;
    }
    if (D_00482374 != 0) {
        if (D_00482374->f46 != 0) {
            InsectCageSceneDraw_389ed0();
        }
    }
    UiDrawWidgets_291910(D_004DB1B0);
    DebugItemListDrawIfShown_299d60(D_004DB220);
    DebugItemIconGridDrawInfo_29a680(D_004DB240);
    if (D_00482374 != 0) {
        MenuFadeDraw_29fe50(D_00482374);
    }
    MenuItemModelDraw_2a7090(0, 0, 0, 0);
    if (D_004823D0 != 0) {
        if (D_004823CC != 0) {
            dl = GetDrawCtx_15de80();
            DrawListAddTexLoad_1418c0(dl, 0x288, 1.0f);
            CameraSetViewFromCameraBase_142dd0(dl, D_004823D4, 0, 0);
            DrawListAddCameraMatrixPacket_1481b0(dl);
            DrawListAddViewPacket_1482e0(dl);
            ((CObj *)D_004823D0)->v7();
        }
    }
    MenuWeaponCombineResultModelDraw_2a84f0();
    if (D_00482388 != 0) {
        MenuMobPreviewDraw_35fa50(D_00482388);
    }
    UiDrawWidgets_291910(D_004DB1D0);
}
