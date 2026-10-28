#include "types.h"

typedef struct { f32 x, y, z, w; } Vec;

class Cam {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;      
          
         
       
       
       
       
       
       
      
    void getPos(Vec * a0) { VCM(void, (void *, Vec *), 0xA4, a0); }
};

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
void GsPktSetTexture_13ec00(u8 *, s32);
void GsPktSetUV_13ed60(u8 *, s32, s32);
void GsPktSetRGBAQVec_13edd0(u8 *, s32);
void GsPktSetXYZVecI_13eeb0(u8 *, Vec *);
void GsPktClose_13f5b0(u8 *);
void GsPktOpenPrim_13f730(u8 *, s32);
s32 ProjectToScreen_15d340(Vec *, Vec *);
Cam *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
void VecWeightedSum3_1cb860(Vec *, Vec *, Vec *, Vec *, f32, f32, f32);
void VecLinearCombine_1cb8b0(Vec *, Vec *, Vec *, f32, f32);
void VecCross_1cb9f0(Vec *, Vec *, Vec *);
void VecNormalize_1cbb80(Vec *, Vec *);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
f32 AngleWrap_1cbf30(f32);
u8 *GetCurrentScene_1f5be0(void);
extern f32 D_0047EE50;
extern f32 D_0047EE54;
extern f32 D_0047EE58;
extern f32 D_0047EE5C;
void DrawCameraFacingQuad_2d4d40(u8 *dst, Vec *pos, s32 *rect, s32 arg3, s32 arg4, f32 w, f32 h, f32 ang);
}

void DrawCameraFacingQuad_2d4d40(u8 *dst, Vec *pos, s32 *rect, s32 arg3, s32 arg4, f32 w, f32 h, f32 ang) {
    Vec eye __attribute__((aligned(16)));
    Vec dir __attribute__((aligned(16)));
    Vec side __attribute__((aligned(16)));
    Vec up __attribute__((aligned(16)));
    Vec va __attribute__((aligned(16)));
    Vec vb __attribute__((aligned(16)));
    Vec c3 __attribute__((aligned(16)));
    Vec c2 __attribute__((aligned(16)));
    Vec c1 __attribute__((aligned(16)));
    Vec c0 __attribute__((aligned(16)));
    Vec s3 __attribute__((aligned(16)));
    Vec s2 __attribute__((aligned(16)));
    Vec s1 __attribute__((aligned(16)));
    Vec s0 __attribute__((aligned(16)));
    u8 *m;
    Cam *cam;
    f32 sn;
    f32 cs;

    m = GetCurrentScene_1f5be0();
    cam = ObjRecGetLiveObject_1c3bc0(m, *(s32 *)(m + 0x4344));
    up.x = D_0047EE50;
    up.y = D_0047EE54;
    up.z = D_0047EE58;
    up.w = D_0047EE5C;
    cam->getPos(&eye);
    VecSub_1cbd00(&dir, pos, &eye);
    VecNormalize_1cbb80(&dir, &dir);
    VecCross_1cb9f0(&side, &up, &dir);
    VecNormalize_1cbb80(&side, &side);
    VecCross_1cb9f0(&up, &dir, &side);
    w = w * 0.5f;
    h = h * 0.5f;
    ang = AngleWrap_1cbf30(ang);
    sn = Sinf_128fd0(ang);
    cs = Cosf_128d30(ang);
    VecLinearCombine_1cb8b0(&va, &side, &up, w * cs, w * sn);
    VecLinearCombine_1cb8b0(&vb, &side, &up, -h * sn, h * cs);
    VecWeightedSum3_1cb860(&c0, &va, &vb, pos, -1.0f, 1.0f, 1.0f);
    VecWeightedSum3_1cb860(&c1, &va, &vb, pos, 1.0f, 1.0f, 1.0f);
    VecWeightedSum3_1cb860(&c2, &va, &vb, pos, -1.0f, -1.0f, 1.0f);
    VecWeightedSum3_1cb860(&c3, &va, &vb, pos, 1.0f, -1.0f, 1.0f);
    if (ProjectToScreen_15d340(&s0, &c0) == 0) {
        return;
    }
    if (ProjectToScreen_15d340(&s1, &c1) == 0) {
        return;
    }
    if (ProjectToScreen_15d340(&s2, &c2) == 0) {
        return;
    }
    if (ProjectToScreen_15d340(&s3, &c3) == 0) {
        return;
    }
    GsPktOpenPrim_13f730(dst, 4);
    GsPktSetTexture_13ec00(dst, arg3);
    GsPktSetRGBAQVec_13edd0(dst, arg4);
    GsPktSetUV_13ed60(dst, rect[0], rect[1]);
    GsPktSetXYZVecI_13eeb0(dst, &s0);
    GsPktSetUV_13ed60(dst, rect[0] + rect[2], rect[1]);
    GsPktSetXYZVecI_13eeb0(dst, &s1);
    GsPktSetUV_13ed60(dst, rect[0], rect[1] + rect[3]);
    GsPktSetXYZVecI_13eeb0(dst, &s2);
    GsPktSetUV_13ed60(dst, rect[0] + rect[2], rect[1] + rect[3]);
    GsPktSetXYZVecI_13eeb0(dst, &s3);
    GsPktClose_13f5b0(dst);
}
