#include "types.h"
/* normal 0x004F6F80 -- sibling of 00501D40/005058D0: same colour-table
 * search tail against D_00524FC0.  `b` is passed straight through to
 * func_28FE10 as its id argument and is otherwise unread here. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
} Obj;

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

typedef struct Root {
    u8    pad000[0x18];
    void *f018;
} Root;

typedef struct St {
    u8  pad00[0x2C];
    s16 f2C;
} St;

extern const s16 D_00524FC0[0x21];

extern SA   *func_28FE10(void *w, s32 id, s32 n);
extern Root *func_1FEDE0(void);
extern void *func_3C2420(void *w, s32 i);
extern St   *func_3AE3E0(void *o);

s32 normal_FieldHudPanelSetPortrait_4f6f80(Obj *a, s32 b, s32 c)
{
    SA   *r;
    Root *root;
    void *obj;
    St   *st;
    s16   tbl[0x21];
    s16  *src;
    s16  *dst;
    s32   i;
    s16   target;

    if (a->f378 == 0) {
        return 0;
    }
    if (a == 0) {
        return 0;
    }
    r = func_28FE10(a, b, 0);
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
    src = (s16 *)D_00524FC0;
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
    return 0;
}
