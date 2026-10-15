#include "types.h"
#include "vec.h"
#undef NULL
#define NULL 0
extern "C" {

class Body {
public:
    u8 pad0[0x20];
    Vec4 x20;
    Vec4 x30;
    u8 pad40[0x10];
    virtual void v0();
    virtual s32 Check(s32);
};

class Body2 : public Body {
public:
    u8 pad60[0xA0];
    Vec4 x100;
    Vec4 x110;
    f32 x120;
    u8 pad124[4];
    s32 x128;
    u32 x12C;
};

typedef struct {
    u8 pad0[0xA0];
    Vec4 xA0;
    Vec4 xB0;
    Vec4 xC0;
    Vec4 xD0;
} Frame;

typedef struct {
    u8 pad0[4];
    void **x4;
} Table;

typedef struct Node {
    struct Node *next;
    u8 pad4[0x10];
    s32 x14;
    u8 pad18[0x4];
    s32 x1C;
    s32 x20;
} Node;

typedef struct {
    u8 pad0[0x104];
    Table *x104;
} Ctx;

typedef struct {
    u8 pad0[0xC];
    Table *xC;
    u8 pad10[0x34];
    Node *x44;
} Scene;

extern void AabbTransformBounds_13c710(Vec4 *, Vec4 *, Mtx4 *, Vec4 *, Vec4 *);
extern void MtxInverse_13cf40(Mtx4 *, Mtx4 *);
extern void MtxMul_13d240(Mtx4 *, Mtx4 *, Mtx4 *);
extern void BBoxUnion_13dea0(Vec4 *, Vec4 *);
extern void ModelCalcNodesBoundsMaybe_1531c0(Vec4 *, Vec4 *, Table *, s32, s32, s32);

#pragma opt_common_subs off
#pragma opt_propagation off
void ModelUpdateBoundsProjectedMaybe_14ff90(Ctx *ctx, Scene *sc, Mtx4 *arg2)
{
    Vec4 bb[2];
    Vec4 v150;
    Vec4 v140;
    Mtx4 m;
    Mtx4 inv;
    Mtx4 t;
    Node *node;
    Table *tbl;
    Frame *fr;
    u8 *data;
    Body2 *b;
    bool flag;
    f32 f;
    s32 n;

    node = sc->x44;
    tbl = sc->xC;
    while (node != NULL) {
        data = (u8 *)node + 0x10;
        fr = (Frame *)ctx->x104->x4[node->x14];
        if (fr == NULL) {
            break;
        }
        b = (Body2 *)tbl->x4[*(s32 *)(data + 8)];
        if (b == NULL) {
            return;
        }
        if (b->Check(2) != 0) {
            n = b->x128;
            flag = false;
            if (n > 0) {
                if (b->x12C != 0) {
                    flag = true;
                } else {
                    flag = flag;
                }
            }
            if (flag & 0xFF) {
                ModelCalcNodesBoundsMaybe_1531c0(&bb[0], &b->x100, ctx->x104, *(s32 *)(data + 4), b->x12C, n);
                f = b->x120;
                bb[0].x += f;
                bb[0].y += f;
                bb[0].z += f;
                bb[1].x -= f;
                bb[1].y -= f;
                bb[1].z -= f;
            } else {
                bb[0] = b->x100;
                bb[1] = b->x110;
            }
            m.r[0] = fr->xA0;
            m.r[1] = fr->xB0;
            m.r[2] = fr->xC0;
            m.r[3] = fr->xD0;
            MtxInverse_13cf40(&inv, &m);
            MtxMul_13d240(&t, arg2, &m);
            {
                Mtx4 *p = &t;
                MtxMul_13d240(p, &inv, p);
            }
            AabbTransformBounds_13c710(&v140, &v150, &t, &bb[0], &bb[1]);
            BBoxUnion_13dea0(&bb[0], &v140);
            b->x20 = bb[0];
            b->x30 = bb[1];
        }
        node = node->next;
    }
}

}
