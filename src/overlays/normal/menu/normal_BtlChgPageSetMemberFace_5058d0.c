#include "types.h"
/* normal 0x005058D0 -- sibling of 00501D40/004F6F80: same colour-table search
 * against D_005257B0, but `p` is transformed through
 * normal_UiPageGetLayout_289b60 first, the widget field read is +0x20 (not
 * +0x28), the fourth parameter `d` is dead, and on success it additionally
 * calls func_290F60(p, id, 2, -4) and returns 1 instead of 0. */

typedef struct Ctx Ctx;

typedef struct SA {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x10];
} SA;

typedef struct Wgt {
    u8   pad00[0x20];
    SA  *f20;
} Wgt;

typedef struct Root {
    u8    pad000[0x18];
    void *f018;
} Root;

typedef struct St {
    u8  pad00[0x2C];
    s16 f2C;
} St;

extern const s16 D_005257B0[0x21];

extern void *normal_UiPageGetLayout_289b60(Ctx *p);
extern Wgt  *func_290460(void *w, s32 id);
extern Root *func_1FEDE0(void);
extern void *func_3C2420(void *w, s32 i);
extern St   *func_3AE3E0(void *o);
extern void  func_290F60(void *w, s32 id, s32 c, s32 d);

s32 normal_BtlChgPageSetMemberFace_5058d0(Ctx *p, s32 id, s32 c, s32 d)
{
    void *w2;
    Wgt  *w;
    SA   *r;
    Root *root;
    void *obj;
    St   *st;
    s16   tbl[0x21];
    s16  *src;
    s16  *dst;
    s32   i;
    s16   target;

    w2 = normal_UiPageGetLayout_289b60(p);
    if (w2 == 0) {
        return 0;
    }
    w = func_290460(w2, id);
    if (w == 0) {
        return 0;
    }
    r = w->f20;
    if (r == 0) {
        return 0;
    }
    st = 0;
    if (c != -1) {
        root = func_1FEDE0();
        if (root == 0) {
            return 1;
        }
        obj = func_3C2420(root->f018, c);
        if (obj == 0) {
            return 2;
        }
        st = func_3AE3E0(obj);
        if (st == 0) {
            return 3;
        }
    }
    src = (s16 *)D_005257B0;
    dst = tbl;
    i = 0x21;
    do {
        *dst++ = *src++;
        i--;
    } while (i > 0);
    target = st->f2C;
    r->f0A = 0;
    r->f08 = 0;
    for (i = 0; i < 10; i++) {
        if (tbl[i * 3] == target) {
            r->f08 = tbl[i * 3 + 1];
            r->f0A = tbl[i * 3 + 2];
        }
    }
    r->f0C = 0x4C;
    r->f04 = 0x4C;
    r->f0E = 0x12;
    r->f06 = 0x12;
    func_290F60(w2, id, 2, -4);
    return 1;
}
