#include "types.h"
/* normal 0x005117D0 -- `jr $31 / lw $2,0x1C($4)`. */

typedef struct Obj { u8 pad00[0x1C]; s32 f1C; } Obj;

s32 normal_SpaceMenuGetPickedDest_5117d0(Obj *p)
{
    return p->f1C;
}
