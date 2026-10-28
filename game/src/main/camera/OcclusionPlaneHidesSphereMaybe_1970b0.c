/* rgp:protos */
#define RGP_SELF_OcclusionPlaneHidesSphereMaybe_1970b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B {
    u8 pad0[8];
    f32 f8;
    f32 fC;
} B;

typedef struct A {
    s32 x0;
    u8 pad4[0x50 - 4];
    s32 x50;
    u8 pad54[0x60 - 0x54];
    u8 v060[0xC];
    f32 f6C;
    u8 v070[0x10];
    u8 v080[0x10];
    u8 v090[0x10];
    u8 v0A0[0x18];
    f32 fB8;
} A;

/*rgp*/

u8 OcclusionPlaneHidesSphereMaybe_1970b0(A *a, B *b)
{ RG_VU0_FRAME;
    u8 v;
    f32 t;

    if (a->x0 == 0 || a->x50 == 0) {
        return 0;
    }
    if (a->fB8 < b->f8 - b->fC) {
        return 0;
    }
    t = Vu0InnerProduct_13bd60(&a->v060, (void *)b);
    if (t + a->f6C < b->fC) {
        return 0;
    }
    if (Vu0InnerProduct_13bd60(&a->v070, b) < b->fC) {
        return 0;
    }
    if (Vu0InnerProduct_13bd60(&a->v080, b) < b->fC) {
        return 0;
    }
    if (Vu0InnerProduct_13bd60(&a->v090, b) < b->fC) {
        return 0;
    }
    return !(Vu0InnerProduct_13bd60(&a->v0A0, b) < b->fC);
}
