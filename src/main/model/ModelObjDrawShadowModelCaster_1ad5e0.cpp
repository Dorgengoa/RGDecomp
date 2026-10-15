#include "types.h"
#pragma opt_propagation off

class VE1AD5E0 {
public:
    u8 pad000[0x1B0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual s32 v3(void);
};

extern "C" s32 ModelDrawShadowCaster_14f5d0(void *, s32, void *);
extern "C" void *ModelGetRootFrame_1511a0(void *);
extern "C" void ModelSetRootFramesXform_151500(void *, void *);
extern "C" void ModelAttachRootFrames_1515b0(void *, s32);
extern "C" s32 GetDrawCtx_15de80(void);

/* PARK: 2 bad -- retail computes a2 (temp_17+0x120) BEFORE the a0 move and
   sinks `move a0,s1` into the jal delay slot; we do the reverse.  11 arms
   (named local, four cast spellings, typed struct member, &member, callee
   parameter types) are ONE object.  Same class as s23's SpatialMgrListItemNew_315bd0. */
extern "C" s32 ModelObjDrawShadowModelCaster_1ad5e0(VE1AD5E0 *arg0)
{
    s32 temp_18;
    void *temp_17;
    void *temp_2;
    void *t3;

    if (arg0->v3() == 0) {
        return 0;
    }
    temp_18 = GetDrawCtx_15de80();
    temp_17 = (u8 *)arg0 + 0x270;
    temp_2 = ModelGetRootFrame_1511a0(arg0);
    ModelSetRootFramesXform_151500(temp_17, temp_2);
    if (temp_2 != NULL) {
        ModelAttachRootFrames_1515b0(temp_17, *(s32 *)((u8 *)temp_2 + 0x4));
    } else {
        ModelAttachRootFrames_1515b0(temp_17, 0);
    }
    t3 = (u8 *)temp_17 + 0x120;
    return ModelDrawShadowCaster_14f5d0(temp_17, temp_18, t3);
}
