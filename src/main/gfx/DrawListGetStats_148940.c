#include "types.h"

struct Obj0 {
    s32 m00;
    s32 m04;
};

struct Node {
    u8  pad000[0x2C];
    s32 m2C;
    u8  pad030[4];
    s32 m34;
};

extern struct Obj0 *DrawListGetCurBufHeader_1427c0(void *);
extern struct Node *DrawListGetCurBuf_142790(void *);

void DrawListGetStats_148940(struct Obj0 *p0, s32 *p1, s32 *p2, s32 *p3, s32 *p4)
{
    struct Obj0 *b;
    struct Node *c;

    b = DrawListGetCurBufHeader_1427c0(p0);
    c = DrawListGetCurBuf_142790(p0);
    *p1 = ((p0->m04 - b->m00) / 4) * 4;
    *p3 = b->m04 * 16;
    *p2 = c->m2C * 16;
    *p4 = c->m34 * 16;
}
