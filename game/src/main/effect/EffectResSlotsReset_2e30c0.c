/* rgp:protos */
#define RGP_SELF_EffectResSlotsReset_2e30c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(void *, s32, s32);

struct E {
    u8 pad000[0x174];
    s32 m174;
    u8 pad178[0x4C];
    u16 m1C4;
    u8 pad1C6[0xE];
    s32 m1D4;
};

void EffectResSlotsReset_2e30c0(s32 p0)
{
    s32 i;
    struct E *e;

    i = 0;
    do {
        e = (struct E *)(p0 + i * 0x70);
        memset(&e->m174, 0, 0x70);
        e->m174 = -1;
        e->m1D4 = -1;
        e->m1C4 = 0xFFFF;
        i = i + 1;
    } while (i < 0x30);
}
