/* rgp:protos */
#define RGP_SELF_ShadowMapBuildProjMaterialMaybe_146b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Straight-line spawn path.  Every early exit is a `return`, and the
   `if (p) p->vt = ...` before the unconditional MeshMaterialReset_14b230 call is the
   allocation null-guard, not an if/else. */

struct Node {
    u8 pad000[0x28];
    u8 *m28;   /* 0x28 */
    s32 m2C;   /* 0x2C */
};

struct O1 {
    u8 pad000[0xC];
    f32 mC;    /* 0x0C */
    u8 pad010[0x24];
    void *m34; /* 0x34 */
};

struct O2 {
    u8 pad000[0xC];
    void *mC;  /* 0x0C */
    u8 pad010[0x30];
    void *m40; /* 0x40 */
};

struct B {
    u8 pad000[4];
    s32 m04;   /* 0x04 */
};

struct A {
    u8 pad000[0x3AE0];
    f32 m3AE0;   /* 0x3AE0 */
    u8 *m3AE4;   /* 0x3AE4 */
    u8 pad3AE8[0xA8];
    struct O2 *m3B90; /* 0x3B90 */
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u32 D_0046FF90[];

void ShadowMapBuildProjMaterialMaybe_146b90(struct A *a, struct B *b)
{
    struct Node *x;
    void *nd;
    struct O1 *o1;
    struct O2 *o2;
    s32 n;

    x = ((struct Node *)DrawListGetCurBuf_142790(a));
    if (x == 0) {
        return;
    }
    if (b->m04 == 0) {
        return;
    }
    nd = x->m28 + x->m2C * 16;
    if (nd == 0) {
        return;
    }
    a->m3B90 = 0;
    n = ShadowMapWriteTexMtxPktMaybe_147e30(a, nd, &a->m3AE0);
    if (n <= 0) {
        return;
    }
    MemStackAllocQw_14d950(x, n);
    DmaPktAddCallTag_141b80(a, nd);
    o1 = (struct O1 *)MemStackNew_14e230(0x60, x);
    MeshMaterialDescInitShadowProjMaybe_14bb40(o1);
    o1->mC = a->m3AE0;
    o1->m34 = MemStackStrDup_14cff0(a->m3AE4 + 8, x);
    o2 = (struct O2 *)MemStackNew_14e230(0x50, x);
    if (o2 != 0) {
        o2->m40 = D_0046FF90;
    }
    MeshMaterialReset_14b230(o2);
    MeshMaterialBuildPkt_14ac90(o2, o1, x, a);
    o2->mC = a->m3AE4;
    a->m3B90 = o2;
}
