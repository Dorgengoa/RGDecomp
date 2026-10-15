#include "vec.h"

/* MATCHED 100% (mwcps2-3.0.1b210-060308 -O4; also 100% under the local
   3.0.1-020123 stand-in, which is exact here because the function has no
   likely branch).

   The bone/pose writer the backlog names: it installs a computed world matrix
   on a node and marks the node dirty. The caller builds the rows -- rows[0..2]
   multiplied by R(theta) via three MtxMulVec4_13c900 -- and hands them here. */

typedef struct Node {
    u8 pad00[0x29];
    u8 dirty;        /* +0x29 */
    u8 pad2a[0x36];
    Mtx4 world;      /* +0x60 */
} Node;

void ModelFrameSetMatrix_14a190(Node *node, const Mtx4 *m)
{
    node->world.r[0] = m->r[0];
    node->world.r[1] = m->r[1];
    node->world.r[2] = m->r[2];
    node->world.r[3] = m->r[3];
    node->dirty = 1;
}
