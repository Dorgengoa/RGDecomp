#include "types.h"
/* normal 0x00503450 -- checks the 0x1F widget's field pair against a looked-up
 * record and colours it 0xFF404040 when in range, clears it otherwise. */

typedef struct Rec {
    u8  pad00[0x12];
    s16 f12;
    u8  pad14[0x16 - 0x14];
    s16 f16;
} Rec;

typedef struct Fld {
    u8  pad00[4];
    s32 f04;
    u8  pad08[2];
    u8  f0A;
    u8  pad0B[1];
    u32 f0C;
} Fld;

typedef struct Wgt {
    u8   pad00[0x20];
    s32  f20;
    u8   pad24[4];
    Fld *f28;
} Wgt;

typedef struct Root {
    u8  pad000[0x18];
    s32 f018;
} Root;

typedef struct Ent {
    u8  pad00[8];
    s32 f08;
    u8  pad0C[8];
    s32 f14;
} Ent;

typedef struct It {
    u8  pad00[4];
    s16 f04;
} It;

typedef struct Ctx Ctx;

extern void *D_0048449C;       /* gp - 0xCD4 */
extern void *D_004844A0;       /* gp - 0xCD0 */
extern Ctx  *D_00484454;       /* gp - 0xD1C */

extern Rec  *func_28EC60(void *p);
extern Wgt  *func_290460(void *p, u16 id);
extern Root *func_1FEDE0(void);
extern s32   normal_BtlChgPageGetMember_505f90(Ctx *p);
extern void *func_3C2FB0(s32 a, s32 b);
extern void  func_3A8180(void *it, void *o, s32 a, s32 b);
extern void  func_370170(void *it, void *src);
extern Ent  *func_36FFF0(It *it, s32 n);

s32 normal_BtlChgMenuAbilityDetailRefresh_503450(void)
{
    Rec  *r;
    Wgt  *w;
    Fld  *fp;
    Root *root;
    void *ob;
    It    it;
    u8    tmp[0x18];
    s32   id;
    s32   wsum;
    s32   n;
    Ent  *e;

    r = func_28EC60(D_004844A0);
    if (r == 0) {
        return 0;
    }
    w = func_290460(D_0048449C, 0x1F);
    if (w == 0) {
        return 0;
    }
    fp = w->f28;
    if (fp == 0) {
        return 0;
    }
    wsum = r->f12 + r->f16;
    root = func_1FEDE0();
    if (root == 0) {
        return 0;
    }
    id = normal_BtlChgPageGetMember_505f90(D_00484454);
    ob = func_3C2FB0(root->f018, id);
    if (ob == 0) {
        return 0;
    }
    func_3A8180(tmp, ob, 0, -1);
    func_370170(&it, tmp);
    n = it.f04;
    e = func_36FFF0(&it, wsum);
    if (e != 0) {
        if (wsum < n) {
            fp[0].f0A = 2;
            fp[0].f04 = e->f08;
            fp[0].f0C = 0xFF404040;
            fp[1].f0A = 2;
            fp[1].f04 = e->f14;
            fp[1].f0C = 0xFF404040;
        } else {
            fp[0].f04 = 0;
            fp[1].f04 = 0;
        }
    }
    return 1;
}
