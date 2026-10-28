/* rgp:protos */
#define RGP_SELF_InsectCageMsgListInit_384880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00384880 {
    void *f00;
} Obj_FUN_00384880;

/*rgp*/
/*rgp*/
/*rgp*/

void InsectCageMsgListInit_384880(Obj_FUN_00384880 *o, void *rgp_a1)
{
    o->f00 = ConstructNewArray_100710(MemStackNew_14e1b0(0x4210, (void *)rgp_a1), 0, 0, 0x108, 0x40);
    InsectCageMsgListReset_384820(o);
}
