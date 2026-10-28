/* rgp:protos */
#define RGP_SELF_EvSubNodeMoveByVel_252f40 1
#include "port/game_protos.h"
#line 1
/* PARK: m2c's draft has two overlapping huge-offset bare-stack references
   (`sp3060`, and a second struct at `sp3060+0x3060`) that need a full asm
   trace of the frame layout before they can be typed -- too large a stack
   frame to safely guess within this lane's per-unit budget. Not attempted
   beyond the initial m2c read. */
/* s49m: MATCH */
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 min[4]; f32 max[4]; } Box;
typedef struct { u8 pad[0x60]; } Hit;

typedef struct Cfg {
    u8 pad0[0x10];
    V4 vel;
    s32 unk20;
    s32 unk24;
} Cfg;

typedef struct Obj {
    u8 pad0[0x40];
    s32 unk40;
    u8 pad44[0x2C];
    V4 pos;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvSubNodeMoveByVel_252f40(Cfg *arg0, Obj *arg1)
{
    Box box __attribute__((aligned(16)));
    Hit hits[0x80] __attribute__((aligned(16)));
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    V4 c __attribute__((aligned(16)));
    s32 i;
    s32 n;

    if (!(arg1->unk40 < arg0->unk20)) {
        arg1->unk40 = 0;
        return 0;
    }
    VecAdd_13be20(&arg1->pos, &arg1->pos, &arg0->vel);
    if (arg0->unk24 == 1) {
        for (i = 0; i < 3; i++) {
            box.min[i] = 20.0f + (&arg1->pos.x)[i];
            box.max[i] = (&arg1->pos.x)[i] - 20.0f;
        }
        n = SceneMapAreasCollectCollTrisMaybe_1c5090(((s32)GetStaticScene_1c6c70()), hits, &box, 0x80);
        sceVu0CopyVector(&a, &arg1->pos);
        a.y = a.y + 20.0f;
        a.w = 1.0f;
        sceVu0CopyVector(&b, &arg1->pos);
        b.y = b.y - 20.0f;
        b.w = 1.0f;
        if (MeshRaycastWrapper_16f610(hits, n, &a, &b, &c, 1, 0) >= 0) {
            arg1->pos.y = c.y;
        }
    }
    arg1->unk40++;
    return 1;
}
