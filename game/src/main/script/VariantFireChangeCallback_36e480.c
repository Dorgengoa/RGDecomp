/* rgp:protos */
#define RGP_SELF_VariantFireChangeCallback_36e480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S36e480 {
    u8 pad000[0x20];
    void (*m20)(struct S36e480 *, void *, s32, s32);
    u8 pad024[0x4];
    u8 m28;
};

u8 VariantFireChangeCallback_36e480(struct S36e480 *p, s32 a, s32 b)
{
    void (*fp)(struct S36e480 *, void *, s32, s32);
    u8 r;

    r = 0;
    fp = p->m20;
    if (fp != 0) {
        fp(p, &p->m28, a, b);
        r = 1;
    }
    return r;
}
