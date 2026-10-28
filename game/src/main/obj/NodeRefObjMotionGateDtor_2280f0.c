/* rgp:protos */
#define RGP_SELF_NodeRefObjMotionGateDtor_2280f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00471C90[];
extern u8 D_00471D00[];
extern u8 D_00471AA0[];
/*rgp*/

struct Obj_FUN_002280f0 {
    u8 pad000[0xB0];
    const u8 *mB0;
};

void *NodeRefObjMotionGateDtor_2280f0(struct Obj_FUN_002280f0 *o, s16 flag)
{
    if (o != 0) {
        o->mB0 = D_00471C90;
        if (o != 0) {
            o->mB0 = D_00471D00;
            if (o != 0) {
                o->mB0 = D_00471AA0;
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
