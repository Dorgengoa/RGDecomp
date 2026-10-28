/* rgp:protos */
#define RGP_SELF_MemStackCtor_14e030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00458B08[];
extern s32 D_004810A0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
    s32 m18;
    u8 pad01C[0x4];
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
    s32 m34;
    u8 pad038[0x4];
    s32 m3C;
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
    u8 pad050[0x4];
    s32 m54;
};

struct Obj0 *MemStackCtor_14e030(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;

    r0 = ((s32)strcpy(p0, D_00458B08));
    t0 = D_004810A0;
    D_004810A0 = (t0 + 1);
    p0->m54 = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m28 = 0;
    p0->m2C = 0;
    p0->m34 = 0;
    p0->m20 = 0;
    p0->m4C = 0;
    p0->m48 = 0;
    p0->m44 = 0;
    p0->m40 = 0;
    p0->m24 = 0;
    p0->m30 = -1;
    p0->m3C = 0;
    return p0;
}
