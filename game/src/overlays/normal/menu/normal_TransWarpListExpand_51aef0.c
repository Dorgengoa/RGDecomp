/* rgp:protos */
#define RGP_SELF_normal_TransWarpListExpand_51aef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051AEF0 -- the sibling of MERGED normal_TransWarpListCollapse_51ad60 (selfclust
 * 0.817).  Same rebuild of the shop slot list D_00484870: the old list is
 * copied to a 0xC00 stack buffer, the global is zeroed, and every row is
 * walked back.  Where 0051AD60 SKIPS a source row per iterator hit, this one
 * APPENDS a row built from the hit itself.  Frame -0xC70, same layout.
 *
 * BYTE-IDENTICAL (s23) on the FIRST BUILD, written from 0051AD60's closed
 * source with three edits read straight off the listing: the tag constant is
 * 2 not 1, the inner loop APPENDS instead of advancing `p`, and the appended
 * row's f10 is cleared to -1 when all three floats are zero.  The two levers
 * 0051AD60 paid for -- `d` declared before `p`, and the COMMA-OPERATOR loop
 * test that selects retail's `bnel` + duplicated `lw` ([[mwcc-branch-likely-
 * duplication]] in reverse) -- transferred VERBATIM.
 * ⚠ `k = func_426560(e)` must be a NAMED local: retail stores the CALL RESULT
 * into d->f0C (`sw $2`), not the equal-valued parameter (`$19`). */

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
} Ent;                                          /* 0x30 */

typedef struct Itm {
    s16 f00;
    u8  pad02[0x8 - 0x2];
    s32 f08;
    u8  pad0C[0x14 - 0xC];
    s16 f14;
    u8  pad16[0x18 - 0x16];
    s16 f18;
    u8  f1A;
    u8  pad1B[0x20 - 0x1B];
    f32 f20;
    f32 f24;
    f32 f28;
    u8  pad2C[0x40 - 0x2C];
    u32 f40;
} Itm;

typedef struct Sub { u8 pad00[4]; s16 f04; } Sub;
typedef struct Ev  { u8 pad00[0x18]; Sub *f18; } Ev;
typedef struct Q   { s32 x[4]; } Q;
typedef struct It  { s32 x[2]; } It;

extern Ent *D_00484870;      /* gp - 0x900 */
extern s32  D_00484850;      /* gp - 0x920 */

extern void  memcpy(void *dst, void *src, s32 n);
extern void  memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransWarpListExpand_51aef0(s32 a)
{
    It   it __attribute__((aligned(16)));
    Ent  buf[0x40] __attribute__((aligned(16)));
    Q    q __attribute__((aligned(16)));
    Ev  *w;
    Ent *d;
    Ent *p;
    Itm *e;
    s32  f;
    s32  k;
    s16  h;

    memcpy(buf, D_00484870, 0xC00);
    D_00484850 = 0;
    memset(D_00484870, 0, 0xC00);
    w = ((Ev *)GetGameData_1fede0());
    h = w->f18->f04;
    f = 1;
    if (DebugFlagStubRelated_207f30() != 0) {
        f = 0;
    }
    GroupViewCtor_425440(&q, w, h, f);
    IterInit_370170(&it, &q, 0, 0);
    d = D_00484870;
    p = buf;
    while (p->f00 != -1) {
        if (D_00484850 > 0x40) {
            break;
        }
        if (p->f0C == a) {
            d->f00 = 2;
        } else {
            d->f00 = p->f00;
        }
        d->f04 = p->f04;
        d->f0C = p->f0C;
        d->f08 = p->f08;
        d->f10 = p->f10;
        d->f14 = p->f14;
        d->f18 = p->f18;
        d->f20 = p->f20;
        d->f24 = p->f24;
        d->f28 = p->f28;
        D_00484850++;
        d++;
        if (p->f0C == a) {
            while (e = ((Itm *)IterNext_370040(&it)), e != 0) {
                if ((e->f40 & 1) != 0) {
                    k = TranspRowGetGroupIdMaybe_426560(e);
                    if (a == k) {
                        d->f00 = 3;
                        d->f04 = e->f08;
                        d->f0C = k;
                        d->f08 = e->f00;
                        d->f10 = e->f14;
                        d->f14 = e->f18;
                        d->f18 = e->f1A & 1;
                        d->f20 = e->f20;
                        d->f24 = e->f24;
                        d->f28 = e->f28;
                        if (d->f20 == 0.0f && d->f24 == 0.0f && d->f28 == 0.0f) {
                            d->f10 = -1;
                        }
                        D_00484850++;
                        d++;
                    }
                }
            }
        }
        p++;
    }
    d->f00 = -1;
    return 1;
}
