/* rgp:protos */
#define RGP_SELF_GameRecReleaseAllSlots_3ce400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A34 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 rest : 6;
    u8 pad1[0x33];
} A34;

typedef struct A7F0 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 rest : 6;
    u8 pad1[0x7EF];
} A7F0;

typedef struct A84C {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 rest : 6;
    u8 pad1[0x84B];
} A84C;

void GameRecReleaseAllSlots_3ce400(u8 *arg0) {
    A34 *p;
    A7F0 *q;
    A84C *r;
    s32 i;

    p = (A34 *)(arg0);
    for (i = 0; i < 15; i++) {
        p->b0 = 0;
        p->b1 = 0;
        p++;
    }
    q = (A7F0 *)(arg0 + 0x30C);
    for (i = 0; i < 3; i++) {
        q->b0 = 0;
        q->b1 = 0;
        q++;
    }
    r = (A84C *)(arg0 + 0x1ADC);
    for (i = 0; i < 3; i++) {
        r->b0 = 0;
        r->b1 = 0;
        r++;
    }

}
