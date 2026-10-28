/* rgp:protos */
#define RGP_SELF_CharaDataSubRecInit_1eeab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
    u8 m0A;
    u8 pad00B[0x59];
    s32 m64;
};

void CharaDataSubRecInit_1eeab0(struct Obj0 *p0)
{
    p0->m08 = -1;
    p0->m64 = 0;
    p0->m0A = 1;
    MemStackClear_14dff0((struct Obj0 *)((u8 *)p0 + 0xC));
    ListNodeInit_1efa20(p0);
}
