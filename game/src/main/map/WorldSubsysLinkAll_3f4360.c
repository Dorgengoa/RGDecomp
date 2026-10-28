/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkAll_3f4360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_003f4360 {
    u8 pad000[0x4];
    s32 f04;
    s32 f08;
    s32 f0C;
} Obj_FUN_003f4360;

/*rgp*/
/*rgp*/

s32 WorldSubsysLinkAll_3f4360(Obj_FUN_003f4360 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (o->f08 != 0) {
        WorldSubsysLinkIds_3f49c0(o->f08, o->f04, (int)rgp_a2, (int)rgp_a3);
    }
    if (o->f08 != 0) {
        WorldSubsysLinkIds_3f4590(o->f0C, o->f04, 0, 0);
    }
    return 1;
}
