#include "types.h"

/* C++ VIRTUAL (vptr +0xC0, slots 0x18/0x1C = virtuals #4/#5) AND the reason
   the C++ switch alone is 7 words long: `(u8 *)arg0 + 0x10/0x20/0x30` written
   as pointer arithmetic is CSE'd into THREE callee-saved registers (frame
   0xB0 -> 0xD0, +2 saves). Declaring the three rows as real ARRAY MEMBERS of
   the class makes mwcc re-materialise `addiu $aN,$this,K` at every call site,
   which is retail. One of a 3-member clone group (X/Y/Z axes).
   [[levels.d/jalr-is-cpp-virtual]]. */


class VE15F8D0 {
public:
    u8 pad000[0x10];
    u8 m10[0x10];
    u8 m20[0x10];
    u8 m30[0x10];
    u8 pad040[0xC0 - 0x40];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void v4(void *m);
    virtual void v5(void *m);
};
extern "C" {
void VecNormalize_13bd90(void *, void *);
f32 WrapAngle_13c050(f32);
void MtxMul_13d240(void *, void *, void *);
void MtxIdentity_13d2e0(void *);
void sceVu0OuterProduct(void *, void *, void *);
void sceVu0RotMatrixX(void *, void *, f32);
}

extern "C" void CameraBaseRotateLocalX_15f8d0(VE15F8D0 *arg0, f32 fparg0) {
    u8 sp70[0x40];
    u8 sp30[0x40];

    arg0->v4(sp70);
    MtxIdentity_13d2e0(sp30);
    sceVu0RotMatrixX(sp30, sp30, WrapAngle_13c050(fparg0));
    MtxMul_13d240(sp70, sp70, sp30);
    arg0->v5(sp70);
    sceVu0OuterProduct(arg0->m30, arg0->m10, arg0->m20);
    sceVu0OuterProduct(arg0->m10, arg0->m20, arg0->m30);
    VecNormalize_13bd90(arg0->m10, arg0->m10);
    VecNormalize_13bd90(arg0->m20, arg0->m20);
    VecNormalize_13bd90(arg0->m30, arg0->m30);
}
