/* rgp:protos */
#define RGP_SELF_AiGetCurWaypointGoalDistMaybe_2c0f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E2C0 {
    f32 f00;
    u8  pad004[0x1C];
} E2C0;

typedef struct S2C0 {
    u8   pad000[0x1D8];
    E2C0 arr[3];
    u8   pad238[0x18];
    s8   cnt;
    s8   idx;
} S2C0;

f32 AiGetCurWaypointGoalDistMaybe_2c0f40(S2C0 *p)
{
    f32 r;

    if (p->idx < p->cnt) {
        r = p->arr[p->idx].f00;
    } else {
        r = 0.0f;
    }
    return r;
}
