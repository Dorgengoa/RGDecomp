#include "types.h"

/* Same object/vtable shape as MenuItemModelRelease_2a7130 (src/p20w): mwcc places the
   implicit vtable pointer wherever the first virtual function is declared
   relative to the class's plain data members, so a leading `u8 pad[0x1B0]`
   before the virtuals puts the vptr at object offset 0x1B0 -- matching
   this function's `lw $25,0x1B0($4)` / `lw $25,<slot>($25)` / `jalr $25`
   double-load pattern. Reuse the same 21-slot layout; only the two slots
   this function actually calls (index 7 and 15) need real signatures. */

struct C432 {
    u8 pad000[0x1B0];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual void v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
    virtual s32 v13();
    virtual s32 v14();
    virtual void v15(f32 a);
    virtual s32 v16();
    virtual s32 v17();
    virtual s32 v18();
    virtual s32 v19();
    virtual s32 v20();
};

extern "C" s32 DrawListAddTexLoad_1418c0(s32 a0, s32 a1, f32 a2);
extern "C" void CameraSetViewFromCameraBase_142dd0(s32 a0, s32 a1);
extern "C" void DrawListAddCameraMatrixPacket_1481b0(s32 a0);
extern "C" void DrawListAddViewPacket_1482e0(s32 a0);
extern "C" s32 GetDrawCtx_15de80(void);
extern "C" s32 D_004823D4;
extern "C" C432 *D_004824BC;

extern "C" void MenuItemModelDraw_2a7090(void) {
    if (D_004824BC != NULL) {
        D_004824BC->v15(0.5f);
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x209, 1.0f);
        CameraSetViewFromCameraBase_142dd0(GetDrawCtx_15de80(), D_004823D4);
        DrawListAddCameraMatrixPacket_1481b0(GetDrawCtx_15de80());
        DrawListAddViewPacket_1482e0(GetDrawCtx_15de80());
        D_004824BC->v7();
    }
}
