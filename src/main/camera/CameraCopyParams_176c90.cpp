/* main s27m: CLOSED -- C++ virtual (vptr 0xC0, slot 16) + a memberwise copy of a
   {f32 x10 SEPARATE members, s32} struct ([[cpp-memberwise-struct-copy]]); f32[10] loops. */
#include "types.h"
#include "vec.h"

typedef struct {
    f32 f[10];
    s32 w;
} S_176C90;

typedef struct {
    f32 f0; f32 f1; f32 f2; f32 f3; f32 f4; f32 f5; f32 f6; f32 f7; f32 f8; f32 f9;
    s32 w;
} T_176C90;

class C_176C90 {
public:
    u8 pad000[0xC0];
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
    virtual T_176C90 *v16(void);
};

extern "C" void CameraCopyParams_176c90(C_176C90 *arg0, C_176C90 *arg1) {
    T_176C90 *temp_16;

    temp_16 = arg0->v16();
    *arg1->v16() = *temp_16;
    *(u128 *)((u8 *)arg1 + 0x120) = *(u128 *)((u8 *)arg0 + 0x120);
}
