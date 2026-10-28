/* rgp:protos */
#define RGP_SELF_LightStateSetMatrices_15cc00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The store direction of LightStateGetMatrices_15cb50. */

typedef rg_u128 u128;

struct Dst {
    u8 pad000[0x20];
    u128 m20;
    u128 m30;
    u128 m40;
    u128 m50;
    u128 m60;
    u128 m70;
    u128 m80;
    u128 m90;
};

struct Root {
    u8 pad0000[0x36B4];
    struct Dst *m36B4;
};

struct Src {
    u128 m00;
    u128 m10;
    u128 m20;
    u128 m30;
};

extern struct Root *D_004810A4;

void LightStateSetMatrices_15cc00(struct Src *a, struct Src *b)
{
    struct Dst *s;

    s = D_004810A4->m36B4;
    if (s != 0) {
        s->m20 = a->m00;
        s->m30 = a->m10;
        s->m40 = a->m20;
        s->m50 = a->m30;
        s->m60 = b->m00;
        s->m70 = b->m10;
        s->m80 = b->m20;
        s->m90 = b->m30;
    }
}
