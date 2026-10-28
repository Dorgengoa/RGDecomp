/* rgp:protos */
#define RGP_SELF_HitShapeListPairTest_3153d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef rg_u128 u128;

typedef struct {
    u8 pad0[0xC];
    u8 xC;
    u8 padD[0x23];
} Tri;

typedef struct {
    u128 q;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
} Hit;

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    Tri *x18;
    s32 x1C;
    u128 x20;
    s32 x30;
    s32 x34;
    s32 x38;
    u8 x3C;
} Col;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/



s32 HitShapeListPairTest_3153d0(Col *a, Col *b)
{
    //DECLS
    Hit hit __attribute__((aligned(16)));
    s32 obj;
    s32 flags;
    u8 flag;
    s32 hi;
    s32 nhi;
    s32 av;
    s32 bv;
    s32 n;
    s32 m;
    Tri *p;
    s32 i;
    Tri *q;
    s32 j;
    //ENDDECLS

    if (a->x0 == b->x0) {
        return 0;
    }
    if (a->xC == 1) {
        switch (b->xC) {
        case 1:
            obj = a->x1C;
            if (obj == 0) {
                return 0;
            }
            flags = a->x4;
            flag = 0;
            if (flags & 0x100) {
                hi = (flags & 0x800) != 0;
                nhi = hi ^ 1;
                if (nhi) {
                    flag = 1;
                }
            }
            bv = b->x8;
            av = a->x8;
            if (av == bv) {
                if (((unsigned char)ExecInfoCanHitSameGroupMaybe_3a6ff0(obj)) != 0) {
                    goto match;
                }
                goto fail;
            }
            if ((av >= 0 && av < 0xC) || (flags & 0x200)) {
                if (flag) {
                    goto match;
                }
                if (bv >= 0 && bv < 0xC) {
                    if (((unsigned char)ExecInfoCanHitOtherGroupMaybe_3a6f30(obj))) {
                        goto match;
                    }
                    if (b->x4 & 0x4000) {
                        goto match;
                    }
                }
                if (b->x8 >= 0x80 && b->x8 < 0x9C && ExecInfoCanHitOpposingMaybe_3a6e80(obj)) {
                    goto match;
                }
                goto fail;
            }
            if (av < 0x80 || av >= 0x9C) {
                goto fail;
            }
            if (flag) {
                goto match;
            }
            if (bv >= 0x80 && bv < 0x9C && ((unsigned char)ExecInfoCanHitOtherGroupMaybe_3a6f30(obj))) {
                goto match;
            }
            if (b->x8 >= 0 && b->x8 < 0xC && ExecInfoCanHitOpposingMaybe_3a6e80(obj)) {
                goto match;
            }
        fail:
            return 0;
        case 4:
            goto match;
        case 5:
            goto match;
        default:
            goto match;
        }
    }
match:
    n = a->x14;
    p = a->x18;
    m = b->x14;
    for (i = 0; i < n; i++, p++) {
        q = b->x18;
        for (j = 0; j < m; j++, q++) {
            if (HitShapeIntersect_316ba0(&hit, p, q)) {
                b->x20 = hit.q;
                b->x34 = hit.x14;
                b->x38 = hit.x18;
                b->x3C = q->xC;
                return 1;
            }
        }
    }
    return 0;
}
