/* rgp:protos */
#define RGP_SELF_CollMeshQuadTreeCollectTris_16cfe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct QNode {
    f32 x;          /* 0x00 */
    f32 y;          /* 0x04 */
    f32 z;          /* 0x08 */
    u8 padC[4];
    u16 first;      /* 0x10 */
    u16 num;        /* 0x12 */
    struct QNode *child[4];  /* 0x14 */
} QNode;

typedef struct Box {
    s32 m0;         /* 0x00 */
    s32 m4;         /* 0x04 */
    u8 pad8[8];
    f32 minx;       /* 0x10 */
    f32 f14;
    f32 minz;       /* 0x18 */
    f32 f1C;
    f32 maxx;       /* 0x20 */
    f32 f24;
    f32 maxz;       /* 0x28 */
    f32 f2C;
    s32 cnt;        /* 0x30 */
} Box;

typedef struct Tree {
    u8 pad0[0x54];
    u8 *tris;       /* 0x54 */
    f32 *size;      /* 0x58 */
} Tree;

/*rgp*/
extern f32 D_004590B8[];

s32 CollMeshQuadTreeCollectTris_16cfe0(Tree *t, QNode *n, Box *b, s32 d)
{
    s32 cnt;
    s32 n0;
    s32 i;
    f32 r;
    f32 ext;

    n0 = b->cnt;
    if (n0 <= 0) {
        return 0;
    }
    r = (0.5f * t->size[1]) / (f32)d;
    ext = r + (1.0f + 2.0f * (D_004590B8[0] - 1.0f) * r);
    if (!(b->maxx <= n->x + ext)) {
        return 0;
    }
    if (!(b->maxz <= n->z + ext)) {
        return 0;
    }
    if (b->minx < n->x - ext) {
        return 0;
    }
    if (b->minz < n->z - ext) {
        return 0;
    }
    cnt = CollMeshGatherFacesInBox_16cd90(t, t->tris + n->first * 12, n->num, b->m0, b->m4, &b->minx, n0);
    b->cnt -= cnt;
    b->m4 += cnt * 0x60;
    for (i = 0; i < 4; i++) {
        if (n->child[i] != 0) {
            cnt += CollMeshQuadTreeCollectTris_16cfe0(t, n->child[i], b, d * 2);
        }
    }
    return cnt;
}
