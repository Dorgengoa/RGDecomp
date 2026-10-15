/* MATCH (s41a5): D_004659C8 declared as a real-sized array (lui/lo, not
   gp-relative) and the stray `#pragma optimize_for_size off` dropped. */
#include "types.h"
extern "C" {

extern void **PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern u8 D_004659C8[0x400];

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
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void f(f32 x0);
};
typedef struct {
    u8 pad0[0x4];
    void *unk4;
    u8 pad8[0x8];
    s32 unk10;
} T3ba490_arg0;

s32 ObjMgrUpdate_3ba490(T3ba490_arg0 *arg0, f32 fparg0)
{
    s32 temp_17;
    s32 var_18;
    void **temp_2;

    if (arg0->unk10 == 0) {
        return 0;
    }
    if (!(*(u8 *)((u8 *)*(void **)((u8 *)arg0->unk4 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    temp_17 = *(s32 *)D_004659C8;
    var_18 = 0;
    while (var_18 < temp_17) {
        temp_2 = PoolGetUsedElem_36acb0(arg0->unk10, var_18);
        if (temp_2 != NULL) {
            ((VC_0 *)(temp_2))->f(fparg0);
        }
        var_18 += 1;
    }
    return 1;
    return 0;
}

}
