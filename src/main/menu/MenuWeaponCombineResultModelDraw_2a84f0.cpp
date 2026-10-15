#include "types.h"
extern "C" {

extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void CameraSetViewFromCameraBase_142dd0(s32, s32);
extern void DrawListAddCameraMatrixPacket_1481b0(s32);
extern void DrawListAddViewPacket_1482e0(s32);
extern s32 GetDrawCtx_15de80(void);
extern s32 D_004823D4;
extern u8 D_00482494;
extern void *D_004824B8;

class VC_0 {
public:
    u8 pad[0x1B0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void f();
};
void MenuWeaponCombineResultModelDraw_2a84f0(void) {
    if ((D_004824B8 != NULL) && (D_00482494 != 0)) {
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x209, 1.0f);
        CameraSetViewFromCameraBase_142dd0(GetDrawCtx_15de80(), D_004823D4);
        DrawListAddCameraMatrixPacket_1481b0(GetDrawCtx_15de80());
        DrawListAddViewPacket_1482e0(GetDrawCtx_15de80());
        ((VC_0 *)(D_004824B8))->f();
    }
}

}
