/* rgp:protos */
#define RGP_SELF_TexPairCtor_18fb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00459D00[];
extern u8 D_00459D08[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x40];
    s16 m40;
    s16 m42;
    s16 m44;
    s16 m46;
    s16 m48;
    s16 m4A;
    s32 m4C;
    s32 m50;
    s32 m54;
    s32 m58;
};

struct Obj0 *TexPairCtor_18fb70(struct Obj0 *p0)
{
    strcpy(p0, D_00459D00);
    strcpy((struct Obj0 *)((u8 *)p0 + 0x20), D_00459D08);
    p0->m42 = 0x40;
    p0->m40 = 0x40;
    p0->m46 = 0;
    p0->m44 = 0;
    p0->m48 = 0x200;
    p0->m4A = 0x100;
    p0->m4C = 0x20;
    p0->m50 = 1;
    p0->m58 = 0;
    p0->m54 = 0;
    return p0;
}
