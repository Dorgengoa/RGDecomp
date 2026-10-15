#include "types.h"
/* normal 0x00506850 -- two-row panel layout.  The 12-byte clear at $29+0x20 is
 * the written-out `sb` do-while (null test on a frame address mwcc cannot
 * fold, unsigned counter so the bottom test is `bnez`); the vector it clears
 * is then set to 20.0f three times and never read -- retail keeps the stores
 * because the local is address-taken.  Row store order is the pass-33 one:
 * a.x a.y b.w a.w b.h a.h b.x b.y.  This one calls func_289B60 DIRECTLY. */

typedef struct Row  { s16 ax; s16 ay; s16 aw; s16 ah;
                      s16 bx; s16 by; s16 bw; s16 bh;
                      u8 pad10[0x10]; } Row;       /* 0x20 */
typedef struct Hold { u8 pad000[0x20]; Row *f020; } Hold;

extern void *func_289B60(void *p);
extern Hold *func_290460(void *p, u16 id);

s32 normal_LeaderHudWeaponFrameLayout_506850(void *a, u16 id)
{
    f32  v[3];
    u8  *c;
    u32  n;
    void *w;
    Hold *h;
    Row  *r;

    c = (u8 *)v;
    n = 0xC;
    if (c != 0) {
        do {
            *c = 0;
            n--;
            c++;
        } while (n != 0);
    }
    w = func_289B60(a);
    if (w == 0) {
        return 0;
    }
    h = func_290460(w, id);
    if (h == 0) {
        return 0;
    }
    r = h->f020;
    if (r == 0) {
        return 0;
    }
    r[0].ax = 0;
    r[0].ay = 0;
    r[0].bw = 0x2E;
    r[0].aw = 0x2E;
    r[0].bh = 0x2E;
    r[0].ah = 0x2E;
    r[0].bx = 0;
    r[0].by = 0x9C;

    v[0] = 20.0f;
    v[1] = 20.0f;
    v[2] = 20.0f;

    r[1].ax = 0x2E;
    r[1].ay = 0;
    r[1].bw = 0x73;
    r[1].aw = 0x73;
    r[1].bh = 0x11;
    r[1].ah = 0x11;
    r[1].bx = 0x2E;
    r[1].by = 0x9C;

    r[2].ax = -1;
    return 1;
}
