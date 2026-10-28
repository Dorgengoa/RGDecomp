/* rgp:protos */
#define RGP_SELF_PartyLocationGroupIdIsOneMaybe_3cb120 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct U003cb120 {
    s16 h0;
} U003cb120;

typedef struct T003cb120 {
    u8 pad[0x10];
    U003cb120 *f10;
} T003cb120;

typedef struct S003cb120 {
    u8 pad[0x24];
    T003cb120 *f24;
} S003cb120;

s32 PartyLocationGroupIdIsOneMaybe_3cb120(S003cb120 *s)
{
    T003cb120 *p;
    U003cb120 *u;
    s32 v;

    p = s->f24;
    if (p != 0) {
        u = p->f10;
    } else {
        u = 0;
    }
    if (u != 0) {
        v = u->h0;
    } else {
        v = -1;
    }
    return v == 1;
}
