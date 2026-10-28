/* rgp:protos */
#define RGP_SELF_EvNodeAttachObjCtor_353620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub_FUN_00353620 {
    u8 pad000[0x4];
} Sub_FUN_00353620;

typedef struct Obj_FUN_00353620 {
    u8 pad000[0xDC];
    const u8 *fDC;
    Sub_FUN_00353620 fE0;
    u8 pad0E4[0xC];
    s32 fF0;
    Sub_FUN_00353620 fF4;
} Obj_FUN_00353620;

extern u8 D_00471E70[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

Obj_FUN_00353620 *EvNodeAttachObjCtor_353620(Obj_FUN_00353620 *o)
{
    EvObjCtor_2f9f00(o);
    o->fDC = D_00471E70;
    EventRecCtor_2e5860(&o->fE0);
    EventRecReset_2e5840(&o->fE0);
    o->fF0 = 0;
    TargetRefCtor_2e71f0(&o->fF4);
    EvNodeAttachObjReset_3535c0(o);
    return o;
}
