#pragma optimization_level 3
#pragma opt_propagation off
#pragma opt_common_subs off
#include "camera_cpp.h"
extern "C" {
void VecNormalize_13bd90(void *,void *);
void VecScale_13be00(void *,void *,f32);
void VecAdd_13be20(void *,void *,void *);
void VecSub_13be40(void *,void *,void *);
Camera *ObjRecGetLiveObject_1c3bc0(void *,s32);
void sceVu0CopyVector(void *,void *);
extern u8 *D_00481F78;
s32 EvSubNodeMoveToCameraFront_252e50(void *arg0,void *arg1) {
    Vec4 eye __attribute__((aligned(16)));
    Vec4 at __attribute__((aligned(16)));
    Vec4 delta __attribute__((aligned(16)));
    Vec4 result __attribute__((aligned(16)));
    void *p;
    Camera *camera;
    s32 limit;
    u8 *ctx;
    limit=*(s32 *)((u8 *)arg0+0x24);
    if(limit>=0 && *(s32 *)((u8 *)arg1+0x40)>=limit) {
        *(s32 *)((u8 *)arg1+0x40)=0; return 0;
    }
    ctx=D_00481F78;
    camera=ObjRecGetLiveObject_1c3bc0(ctx,*(s32 *)(ctx+0x4344));
    camera->getEyeLocal(&eye);
    camera->getAtLocal(&at);
    VecSub_13be40(&delta,&at,&eye);
    p=&delta;VecNormalize_13bd90(p,p);
    p=&delta;VecScale_13be00(p,p,*(f32 *)((u8 *)arg0+0x20));
    VecAdd_13be20(&result,&eye,&delta);
    sceVu0CopyVector((u8 *)arg1+0x70,&result);
    *(s32 *)((u8 *)arg1+0x40)+=1;
    return 1;
}
}
