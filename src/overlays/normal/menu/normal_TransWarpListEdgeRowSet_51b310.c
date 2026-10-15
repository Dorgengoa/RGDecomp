#include "types.h"

typedef struct Ent {
    s16 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s8  f18;
    u8  pad19[7];
    f32 f20;
    f32 f24;
    f32 f28;
    s32 f2C;
} Ent;

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

typedef struct SB {
    s16 f00;
    s16 f02;
    s32 f04;
    s32 f08;
    u32 f0C;
} SB;

typedef struct Sub {
    u8  pad00[4];
    s16 f04;
} Sub;

typedef struct Ev {
    u8   pad00[0x18];
    Sub *f18;
} Ev;

typedef struct Q {
    s32 x[4];
} Q;

typedef struct It {
    s32 x[2];
} It;

extern s16  D_0048074C[4];   /* gp - 0x4A24 */
extern void *D_00484710;     /* gp - 0xA60  */
extern Ent  *D_00484870;     /* gp - 0x900  */

extern Ev  *func_1FEDE0(void);
extern s32  func_207F30(void);
extern SB  *func_28F620(void *w, u16 id, s32 n);
extern SA  *func_28FE10(void *w, u16 id, s32 n);
extern void func_370170(It *it, Q *q);
extern void func_425440(Q *q, Ev *e, s16 w, s32 f);

s32 normal_TransWarpListEdgeRowSet_51b310(s32 a, s32 b)
{
    It   it;
    Q    q;
    Ev  *e;
    SA  *pa;
    SB  *pb;
    s32  f;
    s16  w;
    s16  t;
    s16  k;

    e = func_1FEDE0();
    w = e->f18->f04;
    f = 1;
    if (func_207F30() != 0) {
        f = 0;
    }
    func_425440(&q, e, w, f);
    func_370170(&it, &q);
    pa = func_28FE10(D_00484710, 0x75DA, 0);
    if (pa == 0) {
        return 0;
    }
    pb = func_28F620(D_00484710, 0x75DA, 0);
    if (pb == 0) {
        return 0;
    }
    t = D_0048074C[(s16)a];
    pa[5].f02 = t;
    pb[5].f02 = t;
    k = D_00484870[b].f00;
    if (k == 1) {
        pa[5].f08 = 0x26;
        pa[5].f0A = 0;
        pa[5].f00 = 0x9B;
        pb[5].f00 = 0xB3;
    } else if (k == 2) {
        pa[5].f08 = 0x26;
        pa[5].f0A = 0x14;
        pa[5].f00 = 0x9B;
        pb[5].f00 = 0xB3;
    } else if (k == 3) {
        pa[5].f08 = 0x3A;
        pa[5].f0A = 0;
        pa[5].f00 = 0xAD;
        pb[5].f00 = 0xC7;
    }
    pb[5].f04 = D_00484870[b].f04;
    pb[5].f0C = 0xFF303030;
    return 1;
}
