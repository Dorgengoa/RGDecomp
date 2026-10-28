/* rgp:protos */
#define RGP_SELF_SkillFlowHasLearnableMaybe_3e9580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma opt_scalarize off

#pragma opt_foldconstants off

typedef struct Iter { s32 a; s32 b; } Iter;
typedef struct Key { u8 *p; s32 id; } Key;

typedef struct Ref {
    s16 m0;
    s16 m2;
} Ref;

typedef struct Ev {
    u8 pad0[0xC];
    s16 mC;
    s16 padE;
    Ref *m10;
    s16 m14;
    u8 pad16[6];
} Ev;

typedef struct Scr {
    s16 m0;
    u8 pad2[2];
    s16 m4;
    u8 pad6[2];
    Ev *m8;
    u8 padC[4];
    s16 **m10;
} Scr;

typedef struct Sub8C { u8 pad0[0xC]; u8 *mC; } Sub8C;
typedef struct Sub8 { u8 pad0[0x8C]; Sub8C *m8C; } Sub8;

typedef struct Arg0 {
    u8 pad0[8];
    Sub8 *m8;
    u8 padC[8];
    s32 m14;
    s32 m18;
} Arg0;

typedef struct G { u8 pad0[0xC]; s32 mC; } G;

/*rgp*/
extern void Fprintf_12f9a0(s32, u8 *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern G *D_00449858[0x100];
extern u8 D_00466BD0[0x400];

s32 SkillFlowHasLearnableMaybe_3e9580(Arg0 *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    Ev *ev;
    s32 ok;
    s32 i;
    Ref *r;
    s16 *p;
    u8 *base;
    s32 j;
    s32 id;
    Iter it __attribute__((aligned(16)));
    u8 *obj;
    Key k __attribute__((aligned(16)));
    Scr *s;

    if (arg0->m8 == NULL) {
        return 0;
    }
    base = arg0->m8->m8C->mC;
    if (base != NULL) {
        base += 0x88;
    }
    IterInit_370170(&it, base, (int)rgp_a2, (int)rgp_a3);
    while ((s = ((Scr *)IterNext_370040(&it))) != NULL) {
        if (arg1 >= 0 && s->m0 != arg1) {
            continue;
        }
        obj = ((u8 *)CharaMgrPoolFindByDataId_3a8a70(arg0->m14, s->m0, 1, 1, 0, 0, 0));
        if (obj == NULL) {
            continue;
        }
        if (CharaIsInParty_3ae1d0(obj) == 0) {
            continue;
        }
        ev = s->m8;
        for (i = 0; i < s->m4; i++, ev++) {
            if (ev->m14 != 11 && ev->m14 != 12 && ev->m14 != 13) {
                continue;
            }
            {
                r = ev->m10;
                for (j = 0; j < ev->mC; j++, r++) {
                    p = s->m10[r->m2];
                    if (p == NULL) {
                        continue;
                    }
                    id = r->m0;
                    k.p = obj + 0x2F0;
                    k.id = id;
                    if ((u32)id >= 0xC0) {
                        Fprintf_12f9a0(D_00449858[0]->mC, D_00466BD0);
                        Abort_12de80();
                    }
                    if (Bit64Test_3eee20(k.p, id) != 0) {
                        continue;
                    }
                    id = *p;
                    ok = InvHasItemInCategory_3c7f40(arg0->m18, id, 0, 0) & 0xFF;
                    if (ok == 0 && id == 0x40F2) {
                        ok = InvHasItemInCategory_3c7f40(arg0->m18, 0x410B, 0, 0) & 0xFF;
                    }
                    if (ok != 0) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
