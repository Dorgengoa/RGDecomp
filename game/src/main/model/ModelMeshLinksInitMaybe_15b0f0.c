/* rgp:protos */
#define RGP_SELF_ModelMeshLinksInitMaybe_15b0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x130];
    s32 m130;
};

void ModelMeshLinksInitMaybe_15b0f0(struct Obj0 *p0)
{
    ModelMeshInitMaybe_15c8c0(p0);
    p0->m130 = 0;
}
