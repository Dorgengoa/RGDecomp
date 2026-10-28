/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageListFrameLayout_505af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505AF0 -- lays out a one-row panel, then streams three 0x20-byte
 * blocks of a 0x60-byte rodata template out through func_1319A8 and terminates
 * the list with -1.  The destination is a POINTER that is incremented; the
 * source is INDEXED by the counter.  Every path returns 0. */

typedef struct Blk  { s32 w[8]; } Blk;          /* 0x20 */
typedef struct Tbl  { Blk e[3]; } Tbl;          /* 0x60 */
typedef struct Row  { s16 ax; s16 ay; s16 aw; s16 ah;
                      s16 bx; s16 by; s16 bw; s16 bh;
                      f32 f10; f32 f14; u8 pad18[8]; } Row;
typedef struct Hold { u8 pad000[0x20]; Row *f020; } Hold;

/*rgp*/
/*rgp*/
/*rgp*/
extern void  memcpy(void *dst, void *src, s32 n);
extern Tbl   normal_D_00525750[];

s32 normal_BtlChgPageListFrameLayout_505af0(void *a, u16 id)
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
    UiSetWidgetPos_290f60(w, id, -0x19, -2);
    if (h == 0) {
        return 0;
    }
    r = h->f020;
    if (r == 0) {
        return 0;
    }
    r->ax = 3;
    r->ay = 0x1A;
    r->aw = 0x108;
    r->bw = 4;
    r->ah = 0x4D;
    r->bh = 4;
    r->bx = 0x7E;
    r->by = 0x12;
    r->f10 = -1.0f;
    r->f14 = -1.0f;
    q = (Blk *)((u8 *)r + 0x20);
    buf = normal_D_00525750[0];
    for (i = 0; i < 3; i++) {
        memcpy(q, &buf.e[i], 0x20);
        q++;
    }
    *(s16 *)q = -1;
    return 0;
}
