/* rgp:protos */
#define RGP_SELF_UskStackInit_42e470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00468D58[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    s32 m24;
    s32 m28;
};

void UskStackInit_42e470(struct Obj0 *p0)
{
    StrCopyBounded_42cad0(p0, D_00468D58, -1);
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
}
