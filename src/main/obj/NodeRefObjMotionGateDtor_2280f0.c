#include "types.h"

extern const u8 D_00471C90[];
extern const u8 D_00471D00[];
extern const u8 D_00471AA0[];
extern void OperatorDelete_100840(void *);

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
