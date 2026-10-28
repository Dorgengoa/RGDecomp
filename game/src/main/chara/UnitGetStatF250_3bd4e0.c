/* rgp:protos */
#define RGP_SELF_UnitGetStatF250_3bd4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, GETTER template.
   A plain indexed member read.  Shifts and offset are read off the listing;
   the array bound is a stand-in. */

typedef struct G { u8 pad[0x250]; f32 a[1]; } G;

f32 UnitGetStatF250_3bd4e0(G *p, s32 i)
{
    return p->a[i];
}
