/* rgp:protos */
#define RGP_SELF_AttackObjDtor_3172b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00471B40[];
extern u8 D_00471C20[];
extern u8 D_00471AA0[];
/*rgp*/

struct Obj_FUN_003172b0 {
    u8 pad000[0xB0];
    const u8 *mB0;
};

void *AttackObjDtor_3172b0(struct Obj_FUN_003172b0 *o, s16 flag)
{
    if (o != 0) {
        o->mB0 = D_00471B40;
        if (o != 0) {
            o->mB0 = D_00471C20;
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
