/* rgp:protos */
#define RGP_SELF_CharaGetStatF4C_3b0310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, GETTER template.
   A plain indexed member read.  Shifts and offset are read off the listing;
   the array bound is a stand-in. */

typedef struct G { u8 pad[0x4C]; f32 a[1]; } G;

f32 CharaGetStatF4C_3b0310(G *p, s32 i)
{
    return p->a[i];
}
