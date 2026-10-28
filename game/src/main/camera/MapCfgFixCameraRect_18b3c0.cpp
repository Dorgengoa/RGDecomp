/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0

class VB {
public:
    u8 pad[0x30];
    VC_VPTR_MEMBER;
    
    
    void v3(f32 * a0) { VCM(void, (void *, f32 *), 0x14, a0); }
};

extern "C" {
extern void FrameSetScale_14a2c0(void *arg0, f32 *arg1);
extern void FrameSetRot_14a390(void *arg0, f32 *arg1);
extern void FrameSetPos_14a450(void *arg0, f32 *arg1);
extern void *MemStackNew_14e230(s32 arg0, s32 arg1);
extern float VariantReadVec3_15f6c0(f32 *, s64 *);
extern s8 *SlotGetInt_15f720(s64 *arg0);
extern void * CollFrameCtor_16be30(void *, int, int, int);
extern u8 *FixCameraRecGet_189710(s32 arg0, s32 arg1);
extern void CollFrameSetShape_18b5b0(void *arg0, VB *arg1);
extern VB *CollShapeCtor_18b5e0(VB *arg0);
extern s32 MapCfgIsCameraSkipped_18cb00(void);
extern s32 strcmp(const s8 *arg0, const s8 *arg1);
extern s8 D_00459CF8[];
extern s32 D_00481250;
extern s32 D_0048125C;
extern s32 D_004812CC;
extern s32 D_004812D0;
}

extern "C" s32 MapCfgFixCameraRect_18b3c0(s64 *p, s32 arg1)
{
    u8 *t;
    s8 *name;
    VB *bb;
    void *a;
    f32 v[8] __attribute__((aligned(16)));
    f32 w[4] __attribute__((aligned(16)));

    if (MapCfgIsCameraSkipped_18cb00() != 0) {
        return 1;
    }
    t = FixCameraRecGet_189710(D_00481250, D_004812CC);
    if (t == NULL) {
        return 0;
    }
    name = SlotGetInt_15f720(p++);
    if (name == NULL) {
        return 0;
    }
    a = MemStackNew_14e230(0x100, D_0048125C);
    if (a != NULL) {
        a = CollFrameCtor_16be30(a, 0, 0, 0);
    }
    bb = NULL;
    if (strcmp(name, D_00459CF8) == 0) {
        bb = (VB *)MemStackNew_14e230(0x40, D_0048125C);
        if (bb != NULL) {
            bb = CollShapeCtor_18b5e0(bb);
        }
        VariantReadVec3_15f6c0(v + 4, p);
        v[7] = 1.0f;
        VariantReadVec3_15f6c0(v, p + 3);
        v[3] = 1.0f;
        p += 6;
        bb->v3(v);
        if (a != NULL) {
            if (arg1 >= 8) {
                VariantReadVec3_15f6c0(w, p);
                p += 3;
                FrameSetPos_14a450(a, w);
            }
            if (arg1 >= 11) {
                VariantReadVec3_15f6c0(w, p);
                p += 3;
                FrameSetRot_14a390(a, w);
            }
            if (arg1 >= 14) {
                VariantReadVec3_15f6c0(w, p);
                FrameSetScale_14a2c0(a, w);
            }
        }
    }
    if (a != NULL) {
        CollFrameSetShape_18b5b0(a, bb);
    }
    if (D_004812D0 < *(s32 *)(t + 0x90)) {
        ((void **)(t + 0x94))[D_004812D0] = a;
        D_004812D0++;
    }
    return 1;
}
