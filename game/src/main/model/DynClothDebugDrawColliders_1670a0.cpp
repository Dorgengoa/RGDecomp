/* rgp:protos */
#line 1
#include "types.h"

class Obj1670 {
public:
    u8 data[0xE0];
    VC_VPTR_MEMBER;
    
    void v10(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" {
extern void ModelFrameSetMatrix_14a190(Obj1670 *, s32);
extern void FrameResetXform_14a550(Obj1670 *);
extern void FrameInitFields_14a8d0(Obj1670 *);
extern void ModelDraw_14f6d0(u8 *, s32, u8 *);
extern void ModelSetScale_150ff0(u8 *, s32);
extern void ModelSetPos_151110(u8 *, s32);
extern void ModelDetachRootFrames_151460(u8 *);
extern void ModelAttachRootFrames_1515b0(u8 *, Obj1670 *);
extern s32 GetDrawCtx_15de80(void);
extern u8 D_0046FFA0[];
extern u8 *D_00481150;
}

struct A1670 {
    u8 pad[0xEC];
    s32 n;
    s32 *list;
};

extern "C" void DynClothDebugDrawColliders_1670a0(A1670 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    u8 buf[0xE4] __attribute__((aligned(16)));
    s32 i;
    s32 e;

    if (D_00481150 != NULL) {
        *(u8 **)(buf + 0xE0) = D_0046FFA0;
        ((Obj1670 *)buf)->v10((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
        FrameInitFields_14a8d0((Obj1670 *)buf);
        FrameResetXform_14a550((Obj1670 *)buf);
        *(s32 *)(D_00481150 + 0x170) = 0x3F000000;
        for (i = 0; i < arg0->n; i++) {
            e = arg0->list[i];
            ModelFrameSetMatrix_14a190((Obj1670 *)buf, e + 0x10);
            ModelSetScale_150ff0(D_00481150, e + 0x130);
            ModelSetPos_151110(D_00481150, e + 0x120);
            ModelAttachRootFrames_1515b0(D_00481150, (Obj1670 *)buf);
            ModelDraw_14f6d0(D_00481150, GetDrawCtx_15de80(), D_00481150 + 0x120);
            ModelDetachRootFrames_151460(D_00481150);
        }
    }
}
