#include "types.h"

struct Node {
    u8  pad000[0x28];
    u8  *m28;
    s32 m2C;
};

extern struct Node *DrawListGetCurBuf_142790(void *);
extern s32 DrawPktBuildCameraMatrix_1486c0(void *, void *);
extern void MemStackAllocQw_14d950(struct Node *, s32);
extern void DmaPktAddCallTagIfSet_141bb0(void *, void *);

void DrawListAddCameraMatrixPacket_1481b0(void *p0)
{
    struct Node *n;
    u8 *q;
    s32 cnt;

    n = DrawListGetCurBuf_142790(p0);
    if (n != 0) {
        q = n->m28 + n->m2C * 16;
        if (q != 0) {
            cnt = DrawPktBuildCameraMatrix_1486c0(p0, q);
            if (cnt > 0) {
                MemStackAllocQw_14d950(n, cnt);
                DmaPktAddCallTagIfSet_141bb0(p0, q);
            }
        }
    }
}
