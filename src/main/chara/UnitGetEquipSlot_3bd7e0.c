#include "types.h"

struct Obj0;
struct Obj1;

struct E3BD7E0 {
    u8 pad000[0x24];
};

struct Obj1 {
    u8 pad000[0x78];
    s16 m78;
};

struct Obj0 {
    u8 pad000[0x234];
    struct Obj1 *m234;
    u8 pad238[0x278 - 0x238];
    struct E3BD7E0 m278[8];
};

void *UnitGetEquipSlot_3bd7e0(struct Obj0 *p0, s32 p1)
{
    struct Obj1 *t0;

    t0 = p0->m234;
    if (t0 == 0) {
        return 0;
    }
    if (p1 < 0) {
        goto fail;
    }
    if (p1 >= t0->m78) {
        goto fail;
    }
    if (p1 < 8) {
        goto ok;
    }
fail:
    return 0;
ok:
    return &p0->m278[p1];
}
