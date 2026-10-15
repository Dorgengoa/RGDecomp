#include "types.h"

struct C76 {
    u8 pad000[0x4C];
    virtual s32 v0();
    virtual s32 v1(s32);
};

struct E8 { s32 a; s32 b; };

extern "C" s32 VariantGetInt_15f780(struct E8 *);

struct Obj0 {
    u8 pad000[0x50];
    s32 m50;
    s32 m54;
};

extern "C" struct Obj0 *D_004812D8;

extern "C" s32 MapCfgFuncPlaceData_18a7a0(struct E8 *p0)
{
    struct Obj0 *o;

    if (D_004812D8 == 0) {
        return 0;
    }
    if (((struct C76 *)D_004812D8)->v1(0x271C) == 0) {
        return 0;
    }
    o = D_004812D8;
    o->m50 = VariantGetInt_15f780(p0++);
    o->m54 = VariantGetInt_15f780(p0);
    return 1;
}
