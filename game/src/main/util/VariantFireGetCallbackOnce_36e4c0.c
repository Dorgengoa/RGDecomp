/* rgp:protos */
#define RGP_SELF_VariantFireGetCallbackOnce_36e4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S36e4c0 {
    u8 pad000[0x10];
    void (*m10)(struct S36e4c0 *, void *, s32, s32);
    u8 pad014[0x4];
    u8 m18;
};

u8 VariantFireGetCallbackOnce_36e4c0(struct S36e4c0 *p, s32 a, s32 b)
{
    void (*fp)(struct S36e4c0 *, void *, s32, s32);
    u8 r;

    r = 0;
    fp = p->m10;
    if (fp != 0) {
        fp(p, &p->m18, a, b);
        p->m10 = 0;
        r = 1;
    }
    return r;
}
