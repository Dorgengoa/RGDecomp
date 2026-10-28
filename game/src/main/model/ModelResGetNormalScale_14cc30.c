/* rgp:protos */
#define RGP_SELF_ModelResGetNormalScale_14cc30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V16_FUN_0014cc30 {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} __attribute__((aligned(16))) V16_FUN_0014cc30;

typedef struct Obj_FUN_0014cc30 {
    u8 pad000[0x11];
    u8 mB;
    u8 pad[0x40 - 0x11 - 1];
    V16_FUN_0014cc30 mQ;
} Obj_FUN_0014cc30;

typedef struct H_FUN_0014cc30 {
    Obj_FUN_0014cc30 *m0;
} H_FUN_0014cc30;

/*rgp*/

void ModelResGetNormalScale_14cc30(H_FUN_0014cc30 *h, V16_FUN_0014cc30 *out)
{ __typeof__(out) rgp_entry_out = out;
    Obj_FUN_0014cc30 *p;
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
