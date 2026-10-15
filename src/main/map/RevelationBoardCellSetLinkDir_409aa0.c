#include "types.h"
#pragma opt_propagation off

typedef struct {
    u32 p : 9;
    u32 lvl : 4;
    u32 a : 8;
    u32 q : 11;
} F;

s32 RevelationBoardCellSetLinkDir_409aa0(F *o, s32 n, s32 on)
{
    s32 m;
    s32 r;

    if (n < 0) {
        goto fail;
    }
    if (n > 7) {
fail:
        return 0;
    }
    r = 1;
    m = r << n;
    if (on != 0) {
        if (o->lvl < 10) {
            o->a |= m;
        } else {
            return 0;
        }
    } else {
        o->a &= ~m;
    }
    return r;
}
