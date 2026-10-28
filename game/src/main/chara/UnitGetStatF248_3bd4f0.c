/* rgp:protos */
#define RGP_SELF_UnitGetStatF248_3bd4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, GETTER template.
   A plain indexed member read.  Shifts and offset are read off the listing;
   the array bound is a stand-in. */

typedef struct G { u8 pad[0x248]; f32 a[1]; } G;

f32 UnitGetStatF248_3bd4f0(G *p, s32 i)
{
    return p->a[i];
}
