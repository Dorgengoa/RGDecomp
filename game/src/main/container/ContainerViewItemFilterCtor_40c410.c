/* rgp:protos */
#define RGP_SELF_ContainerViewItemFilterCtor_40c410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_004792E0[];
extern u8 D_00479410[];

struct Obj0;

struct Obj0 {
    void *m00;
};

struct Obj0 *ContainerViewItemFilterCtor_40c410(struct Obj0 *p0, int rgp_a1, short rgp_a2, short rgp_a3, int rgp_a4, int rgp_a5, int rgp_a6, int rgp_a7)
{
    s32 r0;

    p0->m00 = D_00472250;
    p0->m00 = D_00479410;
    p0->m00 = D_004792E0;
    r0 = (ContainerViewItemFilterInit_40c380((void *)p0, (int)rgp_a1, (short)rgp_a2, (short)rgp_a3, (int)rgp_a4, (int)rgp_a5, (int)rgp_a6, (int)rgp_a7), (s32)0);
    return p0;
}
