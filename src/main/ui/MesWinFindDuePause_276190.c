#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0xBC];
    s32 mBC;
    u8 pad0C0[0x18C4 - 0xC0];
    s16 m18C4[16];
    s32 m18E4[16];
};

s32 MesWinFindDuePause_276190(struct Obj0 *p0)
{
    s32 l0;
    s32 t0;
    s16 t1;
    s32 t2;

    l0 = 0;
    while (l0 < 0x10) {
        t0 = p0->mBC;
        t1 = p0->m18C4[l0];
        if (t1 <= t0) {
            t2 = p0->m18E4[l0];
            if (t2 > 0) {
                return l0;
            }
        }
        l0 = (l0 + 1);
    }
    return -1;
}
