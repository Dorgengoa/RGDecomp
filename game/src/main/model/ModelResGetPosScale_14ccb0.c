/* rgp:protos */
#define RGP_SELF_ModelResGetPosScale_14ccb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V16_FUN_0014ccb0 {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} __attribute__((aligned(16))) V16_FUN_0014ccb0;

typedef struct Obj_FUN_0014ccb0 {
    u8 pad000[0x10];
    u8 mB;
    u8 pad[0x20 - 0x10 - 1];
    V16_FUN_0014ccb0 mQ;
} Obj_FUN_0014ccb0;

typedef struct H_FUN_0014ccb0 {
    Obj_FUN_0014ccb0 *m0;
} H_FUN_0014ccb0;

/*rgp*/

void ModelResGetPosScale_14ccb0(H_FUN_0014ccb0 *h, V16_FUN_0014ccb0 *out)
{ __typeof__(out) rgp_entry_out = out;
    Obj_FUN_0014ccb0 *p;
    s32 t;

    p = h->m0;
    if (p == 0) return;
    *out = p->mQ;
    p = h->m0;
    if (p != 0) {
        t = p->mB;
    } else {
        t = 0x20;
    }
    if (t == 8) {
        VecScale_13be00(out, (void *)rgp_entry_out, 256.0f);
    }
}
