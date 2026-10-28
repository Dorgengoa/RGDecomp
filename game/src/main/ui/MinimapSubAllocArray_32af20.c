/* rgp:protos */
#define RGP_SELF_MinimapSubAllocArray_32af20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_0032af20 {
    void *f00;
    s32 f04;
    u8 pad008[0x2];
    s16 f0A;
} Obj_FUN_0032af20;

/*rgp*/
/*rgp*/

void MinimapSubAllocArray_32af20(Obj_FUN_0032af20 *o)
{
    s32 n;

    n = o->f0A;
    o->f00 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 16 + 0x10, o->f04), 0, 0, 0x10, n);
}
