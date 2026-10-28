/* rgp:protos */
#define RGP_SELF_PartyAddJourneyDist_3c96c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad[0x110];
    f64 d110;
    u8 pad2[8];
    f32 f120;
} T_003c96c0;

f64 PartyAddJourneyDist_3c96c0(T_003c96c0 *p, f32 v)
{
    p->d110 = p->d110 + v;
    p->f120 = p->f120 + v;
    return p->d110;
}
