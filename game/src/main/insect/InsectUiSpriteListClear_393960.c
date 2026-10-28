/* rgp:protos */
#define RGP_SELF_InsectUiSpriteListClear_393960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10, f14;
    s16 f18, f1A, f1C, f1E;
} E_00393960;

typedef struct { u8 pad[0x20]; E_00393960 *f20; } T_00393960;

void InsectUiSpriteListClear_393960(void *unused, T_00393960 *p, s32 n)
{
    E_00393960 *e;
    s32 i;
    f32 z;

    if (p == 0) return;
    e = p->f20;
    if (e == 0) return;
    z = 0.0f;
    for (i = 0; i < n; i++) {
        e->f2 = 0;
        e->f0 = 0;
        e->f6 = 0;
        e->f4 = 0;
        e->fA = 0;
        e->f8 = 0;
        e->fE = 0;
        e->fC = 0;
        e->f14 = 0;
        e->f10 = 0;
        e->f1A = (s16)z;
        e->f18 = (s16)z;
        e++;
    }
}
