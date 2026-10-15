#include "types.h"
#include "vec.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Sub00151E20;

typedef struct SNode00151E20 SNode00151E20;
struct SNode00151E20 {
    SNode00151E20 *unk0;
    u8 pad4[0x10 - 4];
    Sub00151E20 unk10;
};

typedef struct {
    u8 pad0[0x20];
    Vec4 unk20;
    Vec4 unk30;
} Elem00151E20;

typedef struct {
    u8 pad0[4];
    Elem00151E20 **unk4;
} Buf00151E20;

typedef struct {
    s32 unk0;
    u8 pad4[0x104 - 4];
    s32 unk104;
} Obj0_00151E20;

typedef struct {
    s32 unk0;
    u8 pad4[0xC - 4];
    Buf00151E20 *unkC;
    u8 pad10[0x44 - 0x10];
    SNode00151E20 *unk44;
} Obj6_00151E20;

typedef struct {
    Vec4 unk0;
    Vec4 unk10;
} Box00151E20;

s32 ArrayGetChecked_152fd0(s32, s32);
void AabbTransformBounds_13c710(Vec4 *, Vec4 *, Mtx4 *, Vec4 *, Vec4 *);
void BBoxUnion_13dea0(Box00151E20 *, Box00151E20 *);
void FrameCalcWorldMatrix_148ff0(s32, Mtx4 *);

s32 ModelCalcBBox_151e20(Obj0_00151E20 *arg0, Box00151E20 *arg1, Obj6_00151E20 *arg2) {
    Box00151E20 box;
    Mtx4 mtx;
    Box00151E20 tmp;
    SNode00151E20 *node;
    Buf00151E20 *buf;
    Sub00151E20 *sub;
    Elem00151E20 *e;
    s32 m;
    s32 found;

    if (arg2 == NULL) {
        arg2 = (Obj6_00151E20 *)((u8 *)arg0 + 0x120);
    }
    if (arg0->unk0 == 0) {
        return 0;
    }
    if (arg2->unk0 == 0) {
        return 0;
    }
    node = arg2->unk44;
    if (node == NULL) {
        return 0;
    }
    buf = arg2->unkC;
    found = 0;
    while (node != NULL) {
        sub = &node->unk10;
        m = ArrayGetChecked_152fd0(arg0->unk104, sub->unk4);
        if (m != 0) {
            e = buf->unk4[sub->unk8];
            if (e != NULL) {
                FrameCalcWorldMatrix_148ff0(m, &mtx);
                if (found == 0) {
                    AabbTransformBounds_13c710(&box.unk0, &box.unk10, &mtx, &e->unk20, &e->unk30);
                    found = 1;
                } else {
                    AabbTransformBounds_13c710(&tmp.unk0, &tmp.unk10, &mtx, &e->unk20, &e->unk30);
                    BBoxUnion_13dea0(&box, &tmp);
                }
            }
        }
        node = node->unk0;
    }
    arg1->unk0 = box.unk0;
    arg1->unk10 = box.unk10;
    return found;
}
