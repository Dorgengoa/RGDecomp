/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkAll_3f9e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_003f9e60 {
    u8 pad000[0x4];
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
} Obj_FUN_003f9e60;

/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldSubsysLinkAll_3f9e60(Obj_FUN_003f9e60 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (o->f08 != 0) {
        WorldSubsysLinkIds_3fae60(o->f08, o->f04, (int)rgp_a2, (int)rgp_a3);
    }
    if (o->f0C != 0) {
        WorldSubsysLinkIds_3fa780(o->f0C, o->f04, 0, 0);
    }
    if (o->f10 != 0) {
        WorldSubsysLinkIds_3fa460(o->f10, o->f04, 0, 0);
    }
    return 1;
}
