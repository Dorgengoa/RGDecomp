/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageCommandFrameLayout_505c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505C30 -- the 0x00505AF0 twin: same guard chain and same row
 * store order, eleven blocks off a 0x160-byte template instead of three. */

typedef struct Blk  { s32 w[8]; } Blk;          /* 0x20 */
typedef struct Tbl  { Blk e[11]; } Tbl;         /* 0x160 */
typedef struct Row  { s16 ax; s16 ay; s16 aw; s16 ah;
                      s16 bx; s16 by; s16 bw; s16 bh;
                      f32 f10; f32 f14; u8 pad18[8]; } Row;
typedef struct Hold { u8 pad000[0x20]; Row *f020; } Hold;

/*rgp*/
/*rgp*/
/*rgp*/
extern void  memcpy(void *dst, void *src, s32 n);
extern Tbl   normal_D_005255F0[];

s32 normal_BtlChgPageCommandFrameLayout_505c30(void *a, u16 id)
{
    Tbl buf __attribute__((aligned(16)));
    void *w;
    Hold *h;
    Row  *r;
    Blk  *q;
    s32   i;

    w = normal_UiPageGetLayout_289b60(a);
    if (w == 0) {
        return 0;
    }
    h = ((Hold *)UiFindWidget_290460(w, id));
    UiSetWidgetPos_290f60(w, id, -0x50, 0x28);
    if (h == 0) {
        return 0;
    }
    r = h->f020;
    if (r == 0) {
        return 0;
    }
    r->ax = 3;
    r->ay = 3;
    r->aw = 0x89;
    r->bw = 4;
    r->ah = 0x68;
    r->bh = 4;
    r->bx = 0x7E;
    r->by = 0x12;
    r->f10 = -1.0f;
    r->f14 = -1.0f;
    q = (Blk *)((u8 *)r + 0x20);
    buf = normal_D_005255F0[0];
    for (i = 0; i < 11; i++) {
        memcpy(q, &buf.e[i], 0x20);
        q++;
    }
    *(s16 *)q = -1;
    return 0;
}
