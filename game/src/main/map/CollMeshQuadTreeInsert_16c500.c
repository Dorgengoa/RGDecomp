/* rgp:protos */
#define RGP_SELF_CollMeshQuadTreeInsert_16c500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    f32 x;
    s32 unk4;
    f32 z;
    f32 half;
    s16 unk10;
    s16 unk12;
    struct Node *child[2][2];
} Node;

typedef struct {
    u8 pad0[4];
    f32 size;
    f32 minSize;
    s32 heap;
} Tree;

typedef struct {
    u8 pad0[8];
    Node *node;
} Out;

typedef struct {
    f32 x0;
    u8 pad4[4];
    f32 z0;
    u8 padC[4];
    f32 x1;
    u8 pad14[4];
    f32 z1;
} Box;

/*rgp*/
extern u8 D_004590B8[];

void CollMeshQuadTreeInsert_16c500(Tree *arg0, Node *arg1, Out *arg2, Box *arg3, s32 arg4)
{
    f32 size;
    f32 r;
    f32 x;
    f32 z;
    f32 lo;
    f32 m;
    f32 hi;
    f32 t;
    s32 ix;
    s32 iz;
    s32 i;
    Node **slot;
    Node *n;

    size = arg0->size / (f32)arg4;
    r = 0.25f * size * (*(f32 *)D_004590B8 - 1.0f);
    m = arg3->x1;
    x = arg1->x;
    lo = x - r;
    t = arg3->x0;
    hi = x + r;
    if (t < hi) {
        ix = 0;
    } else if (!(m <= lo)) {
        ix = 1;
    } else {
        ix = 2;
    }
    m = arg3->z1;
    z = arg1->z;
    lo = z - r;
    t = arg3->z0;
    hi = z + r;
    if (t < hi) {
        iz = 0;
    } else if (!(m <= lo)) {
        iz = 1;
    } else {
        iz = 2;
    }
    if (arg4 > 7 || size < arg0->minSize || ix == 2 || iz == 2) {
        arg2->node = arg1;
        return;
    }
    slot = &arg1->child[ix][iz];
    if (*slot == NULL) {
        n = ((Node *)MemStackNew_14e230(0x30, arg0->heap));
        if (n != NULL) {
            n->unk10 = 0;
            n->unk12 = 0;
            for (i = 0; i < 4; i++) {
                (&n->child[0][0])[i] = NULL;
            }
        }
        *slot = n;
    }
    (*slot)->x = arg1->x + 0.5f * (ix - 0.5f) * size;
    (*slot)->unk4 = 0;
    (*slot)->z = arg1->z + 0.5f * (iz - 0.5f) * size;
    (*slot)->half = r;
    CollMeshQuadTreeInsert_16c500(arg0, *slot, arg2, arg3, arg4 * 2);
}
