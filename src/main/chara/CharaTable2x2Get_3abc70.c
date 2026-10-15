#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, GETTER template.
   A plain indexed member read.  Shifts and offset are read off the listing;
   the array bound is a stand-in. */

typedef struct G { u8 pad[0x250]; f32 m[1][2]; } G;

f32 CharaTable2x2Get_3abc70(G *p, s32 i, s32 j)
{
    return p->m[i][j];
}
