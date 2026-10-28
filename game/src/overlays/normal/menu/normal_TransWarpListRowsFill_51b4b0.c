/* rgp:protos */
#define RGP_SELF_normal_TransWarpListRowsFill_51b4b0 1
#include "port/game_protos.h"
#line 1
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

extern void *D_00484710;     /* gp - 0xA60 */
extern Ent  *D_00484870;     /* gp - 0x900 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransWarpListRowsFill_51b4b0(s32 a)
{
    It   it __attribute__((aligned(16)));
    Q    q __attribute__((aligned(16)));
    Ev  *e;
    SA  *pa;
    SB  *pb;
    s32  f;
    s16  w;
    s32  i;
    s16  k;

    e = ((Ev *)GetGameData_1fede0());
    w = e->f18->f04;
    f = 1;
    if (DebugFlagStubRelated_207f30() != 0) {
        f = 0;
    }
    GroupViewCtor_425440(&q, e, w, f);
    IterInit_370170(&it, &q, 0, 0);
    IterSeek_36fff0(&it, a, 0, 0);
    pa = ((SA *)UiGetWidgetSprite_28fe10(D_00484710, 0x75DA, 0));
    if (pa == 0) {
        return 0;
    }
    pb = ((SB *)UiGetWidgetText_28f620(D_00484710, 0x75DA, 0));
    if (pb == 0) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        k = D_00484870[a + i].f00;
        if (k == 1) {
            pa[i].f04 = pa[i].f06 = pa[i].f0C = pa[i].f0E = 0x14;
            pa[i].f00 = 0x9B;
            pa[i].f08 = 0x26;
            pa[i].f0A = 0;
            pb[i].f00 = 0xB3;
            pb[i].f04 = D_00484870[a + i].f04;
            pb[i].f0C = 0xFF303030;
        } else if (k == 2) {
            pa[i].f04 = pa[i].f06 = pa[i].f0C = pa[i].f0E = 0x14;
            pa[i].f00 = 0x9B;
            pa[i].f08 = 0x26;
            pa[i].f0A = 0x14;
            pb[i].f00 = 0xB3;
            pb[i].f04 = D_00484870[a + i].f04;
            pb[i].f0C = 0xFF303030;
        } else if (k == 3) {
            pa[i].f04 = pa[i].f06 = pa[i].f0C = pa[i].f0E = 0x14;
            pa[i].f00 = 0xAD;
            pa[i].f08 = 0x3A;
            pa[i].f0A = 0;
            pb[i].f00 = 0xC7;
            pb[i].f04 = D_00484870[a + i].f04;
            pb[i].f0C = 0xFF303030;
        } else {
            pa[i].f04 = pa[i].f06 = pa[i].f0C = pa[i].f0E = 0;
            pb[i].f04 = 0;
        }
    }
    return 1;
}
