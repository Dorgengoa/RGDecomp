/* rgp:protos */
#line 1
#include "types.h"

typedef struct RetObj {
    u8 pad00[4];
    s32 unk4;
} RetObj;

struct VE {
    u8 pad00[0x1B0];
    VC_VPTR_MEMBER;
    
    
    s32 v3(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x14, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

typedef struct ArgObj2 {
    u8 pad00[0x444];
    s32 unk444;
} ArgObj2;

extern "C" void DrawCtxGetPlaneShadowMtx_147ab0(s32, void *);
extern "C" s32 ModelEmitDrawPacketsMaybe_14ec20(void *, s32, void *);
extern "C" s32 ModelPrepareDrawMaybe_14f760(void *, s32, void *);
extern "C" void ModelUpdateBoundsProjectedMaybe_14ff90(void *, void *, void *);
extern "C" s32 ModelUpdateFrameWorlds_1502b0(void *, s32);
extern "C" RetObj *ModelGetRootFrame_1511a0(void *);
extern "C" void ModelSetRootFramesXform_151500(void *, RetObj *);
extern "C" void ModelAttachRootFrames_1515b0(void *, s32);
extern "C" s32 GetDrawCtx_15de80(void);

extern "C" s32 ModelObjDrawShadowModel_1ad690(VE *arg0, int rgp_a1, int rgp_a2, int rgp_a3) {
    u8 sp50[0x40] __attribute__((aligned(16)));
    s32 temp_18;
    void *temp_16;
    void *temp_17;
    RetObj *temp_2;
    ArgObj2 *arg0b;

    if (arg0->v3((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 0) {
        return 0;
    }
    arg0b = (ArgObj2 *)arg0;
    temp_18 = GetDrawCtx_15de80();
    temp_17 = (u8 *)arg0 + 0x270;
    temp_2 = ModelGetRootFrame_1511a0(arg0);
    ModelSetRootFramesXform_151500(temp_17, temp_2);
    if (temp_2 != NULL) {
        ModelAttachRootFrames_1515b0(temp_17, temp_2->unk4);
    } else {
        ModelAttachRootFrames_1515b0(temp_17, 0);
    }
    temp_16 = (u8 *)temp_17 + 0x120;
    if (ModelUpdateFrameWorlds_1502b0(temp_17, temp_18) == 0) {
        return 0;
    }
    if (arg0b->unk444 != 0) {
        DrawCtxGetPlaneShadowMtx_147ab0(temp_18, sp50);
        ModelUpdateBoundsProjectedMaybe_14ff90(temp_17, temp_16, sp50);
    }
    if (ModelPrepareDrawMaybe_14f760(temp_17, temp_18, temp_16) == 0) {
        return 0;
    }
    return ModelEmitDrawPacketsMaybe_14ec20(temp_17, temp_18, temp_16);
}
