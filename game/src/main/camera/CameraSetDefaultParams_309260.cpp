#include "types.h"
class Obj {u8 pad[0xC0]; public: VC_VPTR_MEMBER;void f() { VCM0(void, 0x58); } };
extern "C" {


extern void CameraSetControlFlagsMaybe_161d40(void *, s32);
extern void CameraSetClampEaseDivMaybe_161e10(f32);
extern void CameraSetLag_177170(void *,f32, f32);

typedef void (*FnVt58)(void *);

void CameraSetDefaultParams_309260(void *self)
{
    u8 *p = (u8 *)self;
    void *vt;
    FnVt58 fn __attribute__((aligned(16)));

    *(u32 *)(p + 0x178) = 0x42200000;
    *(u32 *)(p + 0x17C) = 0xC1200000;
    *(u32 *)(p + 0x170) = 0x42700000;
    *(u32 *)(p + 0x174) = 0xC1A00000;
    *(u32 *)(p + 0x15C) = 0x42820000;
    *(u32 *)(p + 0x160) = 0x42F00000;
    *(u32 *)(p + 0x16C) = 0;
    CameraSetLag_177170(self,4.0f,2.0f);
    CameraSetControlFlagsMaybe_161d40(self, 1);
    ((Obj *)self)->f();
    CameraSetClampEaseDivMaybe_161e10(20.0f);
}

}
