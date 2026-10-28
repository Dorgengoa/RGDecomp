/* rgp:protos */
#define RGP_SELF_EntrySetBlockName_323960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void * memset(s32, s32, s32);
extern void * strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void * EntrySetBlockName_323960(s32 p0, s32 p1)
{ void * rgp_v0 = 0;
    (rgp_v0 = memset((p0 + 0x34), 0, 0x20));
    if (p1 != 0) {
        (rgp_v0 = strcpy((p0 + 0x34), p1));
    }
return rgp_v0; }
