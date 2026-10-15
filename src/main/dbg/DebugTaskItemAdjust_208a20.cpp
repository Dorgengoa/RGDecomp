#include "types.h"
#pragma inline_intrinsics off

class VE208A20 {
public:
    u8 pad000[0x2C];
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
    virtual s32 v10(void);
    virtual void v11(bool);
};

extern "C" s32 DebugMenuWidgetGetFlags_209de0(VE208A20 *);
extern "C" s32 abs(s32);

extern "C" void DebugTaskItemAdjust_208a20(VE208A20 *arg0, s32 arg1)
{
    s32 t;
    if ((abs(arg1) == 1) && !(DebugMenuWidgetGetFlags_209de0(arg0) & 8)) {
        t = arg0->v10();
        arg0->v11(!t);
    }
}
