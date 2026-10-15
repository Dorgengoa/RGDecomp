#include "types.h"

struct E { u8 b[0x98]; };

struct Thing {
    u8  pad000[0x10];
    s16 m10;
};

struct Holder {
    u8    pad000[0x4];
    void *m04;
    u8    pad008[0x4];
    E    *m0C;
};

struct BigD { s32 v; s32 pad[3]; };
extern BigD D_004644A8;

extern "C" void WorldSubsysZoneEntryApplyAreaXform_41c860(E *e, void *a);

extern "C" s32 WorldSubsysZoneEntryLink_41c480(Holder *o, Thing *p)
{
    s32 idx;
    E  *t;
    E  *e;

    if (p == 0) {
        return 0;
    }
    idx = p->m10;
    if (idx < 0 || idx >= D_004644A8.v) {
        return 0;
    }

    t = o->m0C;
    e = 0;
    if (t != 0) {
        e = &t[idx];
    }
    if (e != 0) {
        WorldSubsysZoneEntryApplyAreaXform_41c860(e, o->m04);
    }
    return 1;
}
