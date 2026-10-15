#include "types.h"
class Obj {u8 pad[0xC0]; public: virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();virtual void v18();virtual void v19();virtual void f(); };
extern "C" {


extern void CameraSetControlFlagsMaybe_161d40(void *, s32);
extern void CameraSetClampEaseDivMaybe_161e10(f32);
extern void CameraSetLag_177170(void *,f32, f32);

typedef void (*FnVt58)(void *);

void CameraSetDefaultParams_309260(void *self)
{
    u8 *p = (u8 *)self;
    void *vt;
    FnVt58 fn;

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
