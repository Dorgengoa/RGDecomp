#include "types.h"

struct B3AD0F0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
};
struct C3AD0F0 : B3AD0F0 {};

extern "C" s32 CharaUnequipWeapon_3ad0f0(struct C3AD0F0 *p, s32 k)
{
    s32 off;

    if (k == 0) goto ok;
    if (k == 1) goto ok;
    return 0;
ok:
    off = k * 2;
    *(s16 *)(off + (s32)p + 0x23E) = -1;
    p->v12();
    return 1;
}
