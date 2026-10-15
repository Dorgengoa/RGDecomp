#include "types.h"

struct E12 { u8 p0[8]; s32 m8; };

class VE16C {
public:
    u8 pad000[0x30];
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
    virtual s32 v12(void);
    u8 pad034[0x54 - 0x34];
    s32 unk54;
};

extern "C" void CollMeshSetTriAttr_16cd10(VE16C *arg0, s32 arg1, s32 arg2)
{
    E12 *temp_4;

    if ((arg1 < 0) || (arg1 >= arg0->v12())) {
        return;
    }
    temp_4 = (E12 *)arg0->unk54;
    if (temp_4 != NULL) {
        temp_4[arg1].m8 = arg2;
    }
}
