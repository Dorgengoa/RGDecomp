#include "types.h"

/* C++ VIRTUAL: vptr +0, slot 0x70 = virtual #26, taking an s16.
   NOTE this image passes the 5th and 6th arguments in $8/$9, so MapAreaSlotLoad_1e2fd0
   really takes SIX. [[levers.d/jalr-is-cpp-virtual]]. */

class VE1E3120;
class VE1E3120 {
public:
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
    virtual void * v26(s16 a);
};
extern "C" {
void *GetGameData_1fede0(void);
void MapAreaSlotLoad_1e2fd0(s32, s32, void *, s32, s32, s32);
}

extern "C" void MapAreaSlotLoadById_1e3120(s32 arg0, s32 arg1, s64 arg2, s32 arg3, s32 arg4)
{
    VE1E3120 *self;
    void *p;

    self = *(VE1E3120 **)((u8 *)*(void **)((u8 *)*(void **)((u8 *)GetGameData_1fede0() + 8) + 0x34) + 8);
    p = self->v26((s16)arg2);
    MapAreaSlotLoad_1e2fd0(arg0, arg1, p, arg3, arg4, -1);
}
