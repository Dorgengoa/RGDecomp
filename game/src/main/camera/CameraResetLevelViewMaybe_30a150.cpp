/* rgp:protos */
#line 1
#include "types.h"
typedef s32 (*FN)();

#include "vec.h"
#undef NULL
#define NULL 0
extern "C" {

void *ObjRecGetLiveObject_1c3bc0(void *, s32);                    /* extern */
void VecScaleToLength_1cb510(void *, void *, f32);                      /* extern */
void VecSub_1cbd00(void *, void *, void *);                  /* extern */
void VecAdd_1cbdc0(void *, void *, void *);                  /* extern */
void VecCopy_1cbe30(void *, void *);                       /* extern */
void GameSceneCameraPop_1ced20(void *);                             /* extern */
void * GetCurrentScene_1f5be0(void);                               /* extern */
extern u8 D_0045B080[0x400];
extern f32 D_0047F1B0;
extern f32 D_0047F1B4;
extern f32 D_0047F1B8;
extern f32 D_0047F1BC;
extern f32 D_0047F1C0;
extern f32 D_0047F1C4;
extern f32 D_0047F1C8;
extern f32 D_0047F1CC;

extern "C++" { class VC_0 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class... VcA> s32 f(VcA... vc_va) { return VCM_FN(s32, (void *, ...), 0xA8)((void *)this, vc_va...); }
}; }
extern "C++" { class VC_1 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class... VcA> s32 f(VcA... vc_va) { return VCM_FN(s32, (void *, ...), 0xA4)((void *)this, vc_va...); }
}; }
extern "C++" { class VC_2 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class... VcA> s32 f(VcA... vc_va) { return VCM_FN(s32, (void *, ...), 0xB4)((void *)this, vc_va...); }
}; }
extern "C++" { class VC_3 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class... VcA> s32 f(VcA... vc_va) { return VCM_FN(s32, (void *, ...), 0xB0)((void *)this, vc_va...); }
}; }
s32 CameraResetLevelViewMaybe_30a150(void) { s32 rgp_v0;
    Vec4 a __attribute__((aligned(16)));
    f32 *p;
    Vec4 b __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));

    struct VV { u8 pad[0x4344]; s32 f; } *v;
    void *o;

    p=(f32*)&a;
    p[0] = D_0047F1B0;
    p[1] = D_0047F1B4;
    p[2] = D_0047F1B8;
    p[3] = D_0047F1BC;
    p=(f32*)&b;
    p[0] = D_0047F1C0;
    p[1] = D_0047F1C4;
    p[2] = D_0047F1C8;
    p[3] = D_0047F1CC;
    v = (struct VV *)GetCurrentScene_1f5be0();
    o = ObjRecGetLiveObject_1c3bc0(v, v->f);
    ((VC_0 *)o)->f(&a);
    ((VC_1 *)o)->f(&b);
    VecSub_1cbd00(&c, &b, &a);
    VecCopy_1cbe30(&a, &b);
    c.y = 0.0f;
    VecScaleToLength_1cb510(&c, &c, 0.25f * *(f32 *)D_0045B080);
    VecAdd_1cbdc0(&b, &b, &c);
    GameSceneCameraPop_1ced20(v);
    o = ObjRecGetLiveObject_1c3bc0(v, v->f);
    ((VC_2 *)o)->f(&a);
    rgp_v0 = ((VC_3 *)o)->f(&b);
    *(Vec4 *)((u8 *)o + 0xE0) = a;
    *(Vec4 *)((u8 *)o + 0xF0) = b;
    *(s32 *)((u8 *)o + 0x16C) = 0;
return rgp_v0; }

}
