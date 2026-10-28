/* rgp:protos */
#define RGP_SELF_EffInstSetAutoDestroy_1a0dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef union Handle {
    u32 all;
    struct { u16 idx; u16 gen; } h;
} Handle;

typedef struct Owner { u8 pad000[0x4]; } Owner;

extern void EffInstOrFlags_1a0d20(Owner *t, Handle h, u32 bits);

void EffInstSetAutoDestroy_1a0dd0(Owner *t, Handle h)
{
    volatile struct { u32 a; u32 b; } k;

    k.b = h.all;

    EffInstOrFlags_1a0d20(t, h, 0x4);
}
