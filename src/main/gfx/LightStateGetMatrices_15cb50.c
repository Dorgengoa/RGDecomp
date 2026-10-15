#include "types.h"

/* Copy the 8 quadwords at +0x20..+0x90 of the global scene object into two
   4-quadword destinations.  Interleaved lq/sq pairs => 8 separate member
   assignments (brief: batched lw/sw = one sub-struct copy, interleaved = N). */

typedef unsigned __int128 u128;

struct Src {
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
    struct Src *m36B4;
};

struct Dst {
    u128 m00;
    u128 m10;
    u128 m20;
    u128 m30;
};

extern struct Root *D_004810A4;

void LightStateGetMatrices_15cb50(struct Dst *a, struct Dst *b)
{
    struct Src *s;

    s = D_004810A4->m36B4;
    if (s != 0) {
        a->m00 = s->m20;
        a->m10 = s->m30;
        a->m20 = s->m40;
        a->m30 = s->m50;
        b->m00 = s->m60;
        b->m10 = s->m70;
        b->m20 = s->m80;
        b->m30 = s->m90;
    }
}
