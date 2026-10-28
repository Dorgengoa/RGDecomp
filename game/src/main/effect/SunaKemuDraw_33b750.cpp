/* rgp:protos */
#line 1
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))

class Camera {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void act(void *buf) { VCM(void, (void *, void *), 0xA4, buf); }
};

extern "C" {
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetUseUV_13e3e0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetFrameMask_13e420(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern s32 GetDrawCtx_15de80(void);
extern void *ObjRecGetLiveObject_1c3bc0(void *, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void SunaKemuParticleDraw_33b8d0(void *, void *, s32);
}


extern "C" void SunaKemuDraw_33b750(void *arg0)
{
    u8 sp60[0x10] __attribute__((aligned(16)));
    s32 temp_2_3;
    s32 temp_2_4;
    void *var_16;
    s32 var_20;
    void *temp_2;
    Camera *temp_2_2;
    f32 zz;

    zz = 0.0f;
    if (F32(arg0, 0xE0) != zz) {
        temp_2 = (void *)(u32)GetCurrentScene_1f5be0();
        if (temp_2 != NULL) {
            temp_2_2 = (Camera *)ObjRecGetLiveObject_1c3bc0(temp_2, S32(temp_2, 0x4344));
            if (temp_2_2 != NULL) {
                temp_2_2->act(sp60);
                temp_2_3 = GetDrawCtx_15de80();
                DrawListAddTexLoad_1418c0(temp_2_3, S32(arg0, 0x14), 1.0f);
                temp_2_4 = DrawListBeginPrim_141b00(temp_2_3);
                GsPktSetOriginMode_13e2f0(temp_2_4, 1);
                GsPktSetTextured_13e400(temp_2_4, 1);
                GsPktSetAlphaBlend_13e500(temp_2_4, 1);
                GsPktSetBlendMode_13e4f0(temp_2_4, 1);
                GsPktEnableAlphaTest_13e4d0(temp_2_4, 0);
                GsPktSetGouraud_13e3b0(temp_2_4, 1);
                GsPktSetTexFilter_13e3d0(temp_2_4, 1);
                GsPktSetZWriteMask_13e430(temp_2_4, 1);
                GsPktSetFrameMask_13e420(temp_2_4, -1);
                GsPktEnableZTest_13e460(temp_2_4, 0);
                GsPktSetUseUV_13e3e0(temp_2_4, 1);
                var_16 = (u8 *)arg0 + 0x18;
                var_20 = 0;
                do {
                    if (S16(var_16, 0x10) > 0) {
                        SunaKemuParticleDraw_33b8d0(arg0, var_16, temp_2_4);
                    }
                    var_20 += 1;
                    var_16 = (u8 *)var_16 + 0x14;
                } while (var_20 < 0xA);
                DrawListEndPrim_141a20(temp_2_3);
            }
        }
    }
}
