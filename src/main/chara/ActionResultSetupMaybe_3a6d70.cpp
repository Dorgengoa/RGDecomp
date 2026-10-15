#include "types.h"
extern "C" {

extern void ActionResultClear_3a6e60(void);
extern s32 ActorFindById_3eb870(void *, s32);
extern void *D_004837B4;

class VC_0 {
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
    virtual s32 f(s64 x0);
};
s32 ActionResultSetupMaybe_3a6d70(void *arg0, s32 arg1, s32 arg2, s16 arg3, s8 arg4, s8 arg5, f32 fparg0)
{
    void **temp_4;

    ActionResultClear_3a6e60();
    if (D_004837B4 == NULL) {
        return 0;
    }
    if (arg1 == 0) {
        return 0;
    }
    if (ActorFindById_3eb870(D_004837B4, arg2) == 0) {
        return 0;
    }
    {
        *(s32 *)((u8 *)arg0 + 0) = arg1;
        *(s32 *)((u8 *)arg0 + 4) = arg2;
        temp_4 = *(void ***)(*(u8 **)(*(u8 **)((u8 *)D_004837B4 + 8) + 0x50) + 0xC);
        *(s32 *)((u8 *)arg0 + 8) = ((VC_0 *)(temp_4))->f(arg3);
        *(s8 *)((u8 *)arg0 + 0xC) = arg4;
        *(f32 *)((u8 *)arg0 + 0x10) = fparg0;
        *(s8 *)((u8 *)arg0 + 0x14) = arg5;
        return 1;
    }
    return 0;
    return 0;
}

}
