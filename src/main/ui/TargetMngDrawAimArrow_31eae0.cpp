#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off
extern "C" {

extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void ModelSetScale_150ff0(void *, void *);
extern void ModelSetRot_151080(void *, void *);
extern void ModelSetPos_151110(void *, void *);
extern s32 GetDrawCtx_15de80(void);
extern void MatGetEulerRot_1cb160(void *, void *);
extern void VecScaleToLength_1cb510(void *, void *, f32);
extern void MatMulVec4Args_1cb7f0(void *, void *, f32, f32, f32, f32);
extern void VecCross_1cb9f0(void *, void *, void *);
extern void VecSub_1cbd00(void *, void *, void *);
extern void *GetVecterCursorObj_1fdb00(void);
extern s32 TargetRefGetPos_2e6a60(void *, void *);
extern s32 TargetMngGetAimMode_31ed60(void *);

extern f32 D_0047D248;
extern f32 D_0047D278;
extern f32 D_0047F2E0;
extern f32 D_0047F2E4;
extern f32 D_0047F2E8;
extern f32 D_0047F2EC;

}

class VC_0 {
public:
    u8 pad[0x1B0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void f(f32 x0);
    virtual void d5();
    virtual void d6();
    virtual void g();
};

struct V4 { f32 x, y, z, w; };

typedef struct {
    u8 pad0[0x90];
    f32 unk90;
    f32 unk94;
    f32 unk98;
    u8 pad9C[0x54];
    f32 unkF0;
    u8 padF4[0xC];
    V4 m[4];
    u8 pad140[0x4];
    f32 unk144;
    f32 unk148;
} T31eae0_arg0;

extern "C" void TargetMngDrawAimArrow_31eae0(T31eae0_arg0 *arg0) {
    V4 sp70;
    V4 sp60;
    V4 sp50;
    V4 sp40;
    V4 buf;
    VC_0 *obj;
    u8 *p;
    u32 n;

    if (arg0->unkF0 <= 20.0f) {
        obj = (VC_0 *)GetVecterCursorObj_1fdb00();
        if (obj == NULL) return;
        switch (TargetMngGetAimMode_31ed60(arg0)) {
        case 2:
            if (TargetRefGetPos_2e6a60((u8 *)arg0 + 0xC0, &sp70) == 0) return;
            arg0->m[3].x = arg0->unk90;
            arg0->m[3].y = arg0->unk94 + arg0->unk144;
            arg0->m[3].z = arg0->unk98;
            arg0->m[3].w = 1.0f;
            VecSub_1cbd00(&arg0->m[2], &sp70, &arg0->m[3]);
            { V4 *p = &sp60; p->x = D_0047F2E0;
            p->y = D_0047F2E4;
            p->z = D_0047F2E8;
            p->w = D_0047F2EC;
            VecCross_1cb9f0(&arg0->m[0], p, &arg0->m[2]); }
            VecCross_1cb9f0(&arg0->m[1], &arg0->m[2], &arg0->m[0]);
            { V4 *q = &arg0->m[0]; VecScaleToLength_1cb510(q, q, arg0->unk148); }
            { V4 *q = &arg0->m[1]; VecScaleToLength_1cb510(q, q, arg0->unk148); }
            { V4 *q = &arg0->m[2]; VecScaleToLength_1cb510(q, q, arg0->unk148); }
            break;
        default:
            return;
        }
        {
            MatGetEulerRot_1cb160(&sp40, &arg0->m[0]);
            { f32 z = 0.0f; f32 o = 1.0f; MatMulVec4Args_1cb7f0(&sp50, &arg0->m[0], z, z, o, o); }
            DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), *(volatile s32 *)((u8 *)obj + 0x4DC), 1.0f);
            *(f32 *)((u8 *)obj + 0x448) = 1.0f;
            p = (u8 *)&buf;
            n = 16;
            if (p != NULL) {
                do {
                    *p = 0;
                    n--;
                    p++;
                } while (n != 0);
            }
            { f32 d = D_0047D248; f32 e = D_0047D278; buf.x = d; buf.y = d; buf.z = e; }
            ModelSetScale_150ff0(obj, &buf);
            ModelSetPos_151110(obj, &sp50);
            ModelSetRot_151080(obj, &sp40);
            obj->f(1.0f);
            obj->g();
        }
    }
}
