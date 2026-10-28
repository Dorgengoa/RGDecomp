/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageDetailFrameLayout_505300 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505300 -- copies a 0x140-byte rodata template onto the stack and
 * feeds it out in ten 0x20-byte blocks through func_1319A8. */

typedef struct Blk  { s32 w[8]; } Blk;              /* 0x20 */
typedef struct Tbl  { Blk e[10]; } Tbl;             /* 0x140 */
typedef struct Hold { u8 pad000[0x20]; Blk *f020; } Hold;

/*rgp*/
/*rgp*/
extern void  memcpy(void *dst, void *src, s32 n);
extern Tbl   normal_D_00525880[];

s32 normal_BtlChgPageDetailFrameLayout_505300(void *a, u16 id)
{
    Tbl buf __attribute__((aligned(16)));
    void *w;
    Hold *h;
    Blk *r;
    s32 i;

    w = normal_UiPageGetLayout_289b60(a);
    if (w == 0) {
        return 0;
    }
    h = ((Hold *)UiFindWidget_290460(w, id));
    if (h == 0) {
        return 0;
    }
    r = h->f020;
    if (r == 0) {
        return 0;
    }
    buf = normal_D_00525880[0];
    for (i = 0; i < 10; i++) {
        memcpy(&r[i], &buf.e[i], 0x20);
    }
    return 1;
}
