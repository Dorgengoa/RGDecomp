/* rgp:protos */
#define RGP_SELF_AiAllySuggestClear_2bb9a0 1
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
    u8 pad000[0x143];
    u8 m143;
};

void AiAllySuggestClear_2bb9a0(struct Obj0 *p0)
{
    AiAllySuggestRecReset_3a80e0((struct Obj0 *)((u8 *)p0 + 0x130));
    p0->m143 = 0xFF;
}
