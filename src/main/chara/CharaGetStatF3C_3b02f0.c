#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, GETTER template.
   A plain indexed member read.  Shifts and offset are read off the listing;
   the array bound is a stand-in. */

typedef struct G { u8 pad[0x3C]; f32 a[1]; } G;

f32 CharaGetStatF3C_3b02f0(G *p, s32 i)
{
    return p->a[i];
}
