#include "types.h"
extern "C" {


typedef unsigned __int128 u128;
typedef struct Vec { u128 q; } Vec;
typedef struct Mtx { Vec r[4]; } Mtx;

typedef struct Node {
    u8 pad0[8];
    struct Node *m8;
    u8 padC[0x94];
    Mtx mA0;
} Node;

typedef struct Scene {
    u8 pad0[4];
    Node **m4;
} Scene;

extern void MtxMulPoint_13c890(Vec *, Mtx *, Vec *);
extern void MtxInverse_13cf40(Mtx *, Mtx *);
extern void BoundsAddPoint_13dee0(Vec *, Vec *, Vec *);

void ModelCalcNodesBoundsMaybe_1531c0(Vec *arg0, Vec *arg1, Scene *arg2, s32 arg3, s32 *arg4, s32 arg5)
{
    Mtx m1;
    Mtx inv;
    Mtx m2;
    Vec lo;
    Vec hi;
    Vec v;
    Node *n;
    Node *c;
    s32 found;
    s32 i;

    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    if (arg2 == NULL) {
        return;
    }
    n = arg2->m4[arg3];
    if (n == NULL) {
        return;
    }
    m1.r[0] = n->mA0.r[0];
    m1.r[1] = n->mA0.r[1];
    m1.r[2] = n->mA0.r[2];
    m1.r[3] = n->mA0.r[3];
    MtxInverse_13cf40(&inv, &m1);
    found = 0;
    for (i = 0; i < arg5; i++) {
        n = arg2->m4[arg4[i]];
        if (n == NULL) {
            continue;
        }
        m2.r[0] = n->mA0.r[0];
        m2.r[1] = n->mA0.r[1];
        m2.r[2] = n->mA0.r[2];
        m2.r[3] = n->mA0.r[3];
        MtxMulPoint_13c890(&v, &inv, &m2.r[3]);
        if (found == 0) {
            found = 1;
            lo = v;
            hi = v;
        } else {
            BoundsAddPoint_13dee0(&lo, &hi, &v);
        }
        c = n->m8;
        if (c != NULL) {
            m2.r[0] = c->mA0.r[0];
            m2.r[1] = c->mA0.r[1];
            m2.r[2] = c->mA0.r[2];
            m2.r[3] = c->mA0.r[3];
            MtxMulPoint_13c890(&v, &inv, &m2.r[3]);
            BoundsAddPoint_13dee0(&lo, &hi, &v);
        }
    }
    if (found != 0) {
        arg0[0] = lo;
        arg0[1] = hi;
    }
}

}
