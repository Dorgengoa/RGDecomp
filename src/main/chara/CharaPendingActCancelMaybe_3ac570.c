#include "types.h"

struct Bits { u8 b0 : 1; u8 rest : 7; };
struct Obj0 { u8 pad000[0x23C]; u8 m23C; u8 pad23D[0x25F]; s16 m49C; s16 m49E; };

s32 CharaPendingActCancelMaybe_3ac570(struct Obj0 *p0)
{
    u8 t0;

    t0 = p0->m23C;
    if ((t0 & 1) == 0) {
        return 0;
    }
    ((struct Bits *)&p0->m23C)->b0 = 0;
    p0->m49C = 0;
    p0->m49E = -1;
    return 1;
}
