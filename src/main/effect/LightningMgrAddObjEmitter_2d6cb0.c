#include "types.h"

struct E {
    u8 pad000[0x30];
    s16 m30;
    u8 pad032[0x6];
    s16 m38;
    s16 m3A;
    u8 m3C;
};

void LightningMgrAddObjEmitter_2d6cb0(u8 *p0, s32 p1, s32 p2)
{
    s32 i;
    struct E *e;
    s16 *q;

    i = 0;
    while (i < 0x10) {
        e = (struct E *)(p0 + i * 48);
        q = &e->m3A;
        if (e->m3A == 0) {
            *q = 1;
            e->m30 = p1;
            e->m38 = p2;
            e->m3C = 0;
            return;
        }
        i = i + 1;
    }
}
