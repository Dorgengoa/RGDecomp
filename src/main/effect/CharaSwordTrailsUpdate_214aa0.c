#include "types.h"

typedef struct { u8 pad[0xB8]; } E_00214aa0;
typedef struct { u8 pad[0x584]; E_00214aa0 *f584; s32 f588; } T_00214aa0;

extern void SwordTrailUpdate_2158c0(E_00214aa0 *, f32);

void CharaSwordTrailsUpdate_214aa0(T_00214aa0 *p)
{
    E_00214aa0 *e;
    s32 i;

    e = p->f584;
    if (e == 0) return;
    i = 0;
    while (i < p->f588) {
        SwordTrailUpdate_2158c0(e, 1.0f);
        i++;
        e++;
    }
}
