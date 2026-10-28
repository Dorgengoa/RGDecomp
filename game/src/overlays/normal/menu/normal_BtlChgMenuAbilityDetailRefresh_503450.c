/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuAbilityDetailRefresh_503450 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuAbilityDetailRefresh_503450(void)
{
    Rec  *r;
    Wgt  *w;
    Fld  *fp;
    Root *root;
    void *ob;
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x8 + sizeof(It)]; char m1[0x10]; })];
    u8    tmp[0x18] __attribute__((aligned(16)));
    s32   id;
    s32   wsum;
    s32   n;
    Ent  *e;

    r = ((Rec *)UiEntryListGetCurrentData_28ec60(D_004844A0));
    if (r == 0) {
        return 0;
    }
    w = ((Wgt *)UiFindWidget_290460(D_0048449C, 0x1F));
    if (w == 0) {
        return 0;
    }
    fp = w->f28;
    if (fp == 0) {
        return 0;
    }
    wsum = r->f12 + r->f16;
    root = ((Root *)GetGameData_1fede0());
    if (root == 0) {
        return 0;
    }
    id = normal_BtlChgPageGetMember_505f90(D_00484454);
    ob = PartyGetSlotChara_3c2fb0(root->f018, id);
    if (ob == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(tmp, ob, 0, -1);
    IterInit_370170(&(*(It *)(rgp_blk1 + 0x8)), tmp, 0, 0);
    n = (*(It *)(rgp_blk1 + 0x8)).f04;
    e = ((Ent *)IterSeek_36fff0(&(*(It *)(rgp_blk1 + 0x8)), wsum, 0, 0));
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
