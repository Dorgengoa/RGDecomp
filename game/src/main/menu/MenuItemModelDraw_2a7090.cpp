/* rgp:protos */
#line 1
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void v7() { VCM0(void, 0x24); }
    
    
    
    
    
    
    
    void v15(f32 a, int rgp_fwd2 = 0, int rgp_fwd3 = 0, int rgp_fwd4 = 0) { VCM(void, (void *, int, int, int, f32), 0x44, rgp_fwd2, rgp_fwd3, rgp_fwd4, a); }
    
    
    
    
    
};

extern "C" s32 DrawListAddTexLoad_1418c0(s32 a0, s32 a1, f32 a2);
extern "C" void CameraSetViewFromCameraBase_142dd0(s32, s32, int, int);
extern "C" void DrawListAddCameraMatrixPacket_1481b0(s32 a0);
extern "C" void DrawListAddViewPacket_1482e0(s32 a0);
extern "C" s32 GetDrawCtx_15de80(void);
extern "C" s32 D_004823D4;
extern "C" C432 *D_004824BC;

extern "C" void MenuItemModelDraw_2a7090(int rgp_a0, int rgp_a1, int rgp_a2, int rgp_a3) {
    if (D_004824BC != NULL) {
        D_004824BC->v15(0.5f, (int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x209, 1.0f);
        CameraSetViewFromCameraBase_142dd0(GetDrawCtx_15de80(), D_004823D4, 0, 0);
        DrawListAddCameraMatrixPacket_1481b0(GetDrawCtx_15de80());
        DrawListAddViewPacket_1482e0(GetDrawCtx_15de80());
        D_004824BC->v7();
    }
}
