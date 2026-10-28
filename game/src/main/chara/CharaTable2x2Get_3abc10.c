/* rgp:protos */
#define RGP_SELF_CharaTable2x2Get_3abc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, GETTER template.
   A plain indexed member read.  Shifts and offset are read off the listing;
   the array bound is a stand-in. */

typedef struct G { u8 pad[0x280]; f32 m[1][2]; } G;

f32 CharaTable2x2Get_3abc10(G *p, s32 i, s32 j)
{
    return p->m[i][j];
}
