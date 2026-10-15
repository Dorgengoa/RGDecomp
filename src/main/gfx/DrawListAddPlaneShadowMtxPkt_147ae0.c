#include "types.h"

struct Node {
    u8  pad000[0x28];
    u8  *m28;
    s32 m2C;
};

extern struct Node *DrawListGetCurBuf_142790(void *);
extern s32 DrawPktBuildPlaneShadowMtx_147eb0(void *, void *, void *, s32);
extern void MemStackAllocQw_14d950(struct Node *, s32);
extern void DmaPktAddCallTag_141b80(void *, void *);

void DrawListAddPlaneShadowMtxPkt_147ae0(void *p0, void *p1)
{
    struct Node *n;
    u8 *q;
    s32 cnt;

    n = DrawListGetCurBuf_142790(p0);
    if (n != 0) {
        q = n->m28 + n->m2C * 16;
        if (q != 0) {
            cnt = DrawPktBuildPlaneShadowMtx_147eb0(p0, q, p1, 0);
            if (cnt > 0) {
                MemStackAllocQw_14d950(n, cnt);
                DmaPktAddCallTag_141b80(p0, q);
            }
        }
    }
}
