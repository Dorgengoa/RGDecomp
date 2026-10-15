#include "types.h"

extern const u8 D_00471C20[];
extern const u8 D_00471AA0[];
extern void OperatorDelete_100840(void *);

struct Obj_FUN_0027a180 {
    u8 pad000[0xB0];
    const u8 *mB0;
};

void *AttackObjBaseDtor_27a180(struct Obj_FUN_0027a180 *o, s16 flag)
{
    if (o != 0) {
        o->mB0 = D_00471C20;
        if (o != 0) {
            o->mB0 = D_00471AA0;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
