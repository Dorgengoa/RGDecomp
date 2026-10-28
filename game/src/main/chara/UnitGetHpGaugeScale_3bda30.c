/* rgp:protos */
#define RGP_SELF_UnitGetHpGaugeScale_3bda30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x27]; s8 f27; } S_003BDA30;
typedef struct { u8 pad[0x234]; S_003BDA30 *f234; } T_003BDA30;

f32 UnitGetHpGaugeScale_3bda30(T_003BDA30 *p)
{
    S_003BDA30 *s;
    f32 r;

    s = p->f234;
    if (s == 0) return 1.0f;
    r = 0.0f;
    switch (s->f27) {
    case 0:
        r = 1.0f;
        break;
    case 1:
        r = 1.5f;
        break;
    case 2:
        r = 2.0f;
        break;
    case 3:
        r = 0.5f;
        break;
    }
    return r;
}
