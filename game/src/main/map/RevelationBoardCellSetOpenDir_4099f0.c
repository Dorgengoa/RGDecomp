/* rgp:protos */
#define RGP_SELF_RevelationBoardCellSetOpenDir_4099f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    __extension__ unsigned int p : 13;
    unsigned int a : 8;
    unsigned int b : 8;
    unsigned int q : 3;
} __attribute__((aligned(4))) F;

s32 RevelationBoardCellSetOpenDir_4099f0(F *o, s32 n, s32 on) {
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
        if (o->a & m) {
            o->b |= m;
        } else {
            return 0;
        }
    } else {
        o->b &= ~m;
    }
    return r;
}
