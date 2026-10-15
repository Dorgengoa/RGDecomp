#include "types.h"
/* `daddiu $2,$0,1` in a PLAIN `bltz` slot: a u8 flag preset to 1 on every
   path, cleared only when both bounds hold ($at from the `&&`). */
typedef struct P3D49A0 { u8 pad000[0x6]; s16 m6; } P3D49A0;
typedef struct D3D49A0 { s32 m00; s32 pad[3]; } D3D49A0;
extern D3D49A0 D_00465B50;
u8 ItemPosInvalid_3d49a0(P3D49A0 *p)
{
    s32 v;
    u8  r;

    v = p->m6;
    r = 1;
    if (v >= 0 && v < D_00465B50.m00) {
        r = 0;
    }
    return r;
}
