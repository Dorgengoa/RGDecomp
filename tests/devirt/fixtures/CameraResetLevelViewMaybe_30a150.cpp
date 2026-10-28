#include "types.h"
typedef s32 (*FN)();

#include "vec.h"
#undef NULL
#define NULL 0
extern "C" {

void *ObjRecGetLiveObject_1c3bc0(void *, s32);                    /* extern */
s32 VecScaleToLength_1cb510(void *, void *, f32);                      /* extern */
s32 VecSub_1cbd00(void *, void *, void *);                  /* extern */
s32 VecAdd_1cbdc0(void *, void *, void *);                  /* extern */
s32 VecCopy_1cbe30(void *, void *);                       /* extern */
s32 GameSceneCameraPop_1ced20(void *);                             /* extern */
void *GetCurrentScene_1f5be0(...);                               /* extern */
extern u8 D_0045B080[0x400];
extern f32 D_0047F1B0;
extern f32 D_0047F1B4;
extern f32 D_0047F1B8;
extern f32 D_0047F1BC;
extern f32 D_0047F1C0;
extern f32 D_0047F1C4;
extern f32 D_0047F1C8;
extern f32 D_0047F1CC;

class VC_0 {
public:
    u8 pad[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual s32 f(...);
};
class VC_1 {
public:
    u8 pad[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual s32 f(...);
};
class VC_2 {
public:
    u8 pad[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual s32 f(...);
};
class VC_3 {
public:
    u8 pad[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual s32 f(...);
};
void CameraResetLevelViewMaybe_30a150(void) {
    Vec4 a;
    f32 *p;
    Vec4 b;
    Vec4 c;

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
    ((VC_3 *)o)->f(&b);
    *(Vec4 *)((u8 *)o + 0xE0) = a;
    *(Vec4 *)((u8 *)o + 0xF0) = b;
    *(s32 *)((u8 *)o + 0x16C) = 0;
}

}
