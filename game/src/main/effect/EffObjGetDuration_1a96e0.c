/* rgp:protos */
#define RGP_SELF_EffObjGetDuration_1a96e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x2C]; f32 f2C; s32 f30; } E_001a96e0;
typedef struct { struct N_001a96e0 *f0; E_001a96e0 *f4; } N_001a96e0;
typedef struct { u8 pad[0x2C]; f32 f2C; s32 f30; u8 pad2[0x30]; N_001a96e0 *f64; } T_001a96e0;

f32 EffObjGetDuration_1a96e0(T_001a96e0 *p)
{
    N_001a96e0 *n;
    E_001a96e0 *e;
    f32 best;

    if (p->f30 != 0) return -1.0f;
    best = 0.0f;
    n = p->f64;
    while (n != 0) {
        e = n->f4;
        if (e->f30 != 0) return -1.0f;
        if (e->f2C > best) best = e->f2C;
        n = (N_001a96e0 *)n->f0;
    }
    return best + p->f2C;
}
