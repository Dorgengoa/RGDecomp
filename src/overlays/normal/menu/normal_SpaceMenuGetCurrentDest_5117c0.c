#include "types.h"
/* normal 0x005117C0 -- `jr $31 / lw $2,0x18($4)`. */

typedef struct Obj { u8 pad00[0x18]; s32 f18; } Obj;

s32 normal_SpaceMenuGetCurrentDest_5117c0(Obj *p)
{
    return p->f18;
}
