/* rgp:protos */
#define RGP_SELF_EffObjCtor_1a9af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00470EB8[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x40];
    void *m40;
    s32 m44;
    u8 m48;
    u8 pad049[0x3];
    s32 m4C;
    u8 pad050[0x4];
    s32 m54;
    s32 m58;
    s32 m5C;
    s32 m60;
    s32 m64;
    u8 m68;
};

struct Obj0 *EffObjCtor_1a9af0(struct Obj0 *p0)
{
    s32 r0;

    r0 = ((s32)EffObjBaseCtor_1a9ed0(p0));
    p0->m40 = D_00470EB8;
    p0->m44 = 0;
    p0->m48 = 0;
    p0->m4C = 0;
    p0->m54 = 0;
    p0->m58 = 1;
    p0->m5C = 0x3F800000;
    p0->m60 = 0x3F800000;
    p0->m68 = 0;
    p0->m64 = 0;
    return p0;
}
